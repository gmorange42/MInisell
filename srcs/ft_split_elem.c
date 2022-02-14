/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:17:57 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:23:23 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_quotes_t(char *str, int *i)
{
	int		j;
	char	quote;

	j = *i;
	if (str[j] == '\'' || str[j] == '\"')
	{
		quote = str[j];
		j += 1;
		while (str[j] != quote && str[j] != '\0')
			j++;
		if (str[j] == '\0')
			return (FALSE);
		if (str[j] == quote)
		{
			j += 1;
			*i = j;
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	ft_check_common_char_t(t_data *data, t_elem *elem, char *str, \
		int *i)
{
	int	j;

	j = *i;
	while (str && str[j] && str[j] != '<' && str[j] != '>' && \
			ft_check_whitespaces(str[j]) == FALSE)
	{
		if (ft_check_quotes_t(str, &j) == FALSE)
			j++;
	}
	if (j != *i)
		ft_cpy_token(data, elem, *i, j);
	*i = j;
	return (0);
}

static int	ft_check_redirection(t_data *data, t_elem *elem, char *str, int *i)
{
	int	j;
	int	redirection;

	j = *i;
	if (str[j] == '<' || str[j] == '>')
	{
		redirection = str[j];
		j += 1;
		while (str[j] == redirection)
			j++;
		ft_cpy_token(data, elem, *i, j);
		*i = j;
		return (TRUE);
	}
	return (FALSE);
}

void	ft_split_elem(t_data *data, t_elem *elem, char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		while (str[i] && ft_check_whitespaces(str[i]) == TRUE)
			i++;
		if (str[i] != '\0')
		{
			ft_check_redirection(data, elem, str, &i);
			ft_check_common_char_t(data, elem, str, &i);
		}
	}
}
