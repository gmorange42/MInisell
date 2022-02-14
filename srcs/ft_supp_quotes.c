/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_supp_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:18:50 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:19:09 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cpy(t_data *data, char *str, int len)
{
	int		i;
	int		j;
	char	*cpy;
	char	quote;

	i = 0;
	j = 0;
	quote = '\0';
	cpy = malloc(sizeof(char) * (len + 1));
	ft_check_malloc(data, cpy);
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			quote = str[i++];
		while (str[i] && str[i] != quote && quote != '\0')
			cpy[j++] = str[i++];
		while (str[i] && str[i] != '\'' && str[i] != '"' && quote == '\0')
			cpy[j++] = str[i++];
		if (str[i] && (str[i] == '\'' || str[i] == '"') && quote != '\0')
			i++;
		quote = '\0';
	}
	cpy[j] = '\0';
	return (cpy);
}

int	ft_count_quotes(char *str)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i += 1;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				count += 2;
		}
		if (str[i])
			i += 1;
	}
	return (count);
}

void	ft_supp_quotes(t_data *data, t_elem *elem)
{
	int		i;
	int		count;
	char	*str;

	i = 0;
	count = 0;
	str = NULL;
	while (elem && elem->params && elem->params[i])
	{
		count = ft_count_quotes(elem->params[i]);
		if (count != 0)
		{
			str = ft_cpy(data, elem->params[i], \
					ft_strlen(elem->params[i]) - count);
			free(elem->params[i]);
			elem->params[i] = ft_strdup_t(data, str, -1);
			free(str);
			str = NULL;
			count = 0;
		}
		i++;
	}
	elem->cmd = ft_strdup_t(data, elem->params[0], -1);
}
