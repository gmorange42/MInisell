/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:18:42 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:18:45 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_cpy_param(t_data *data, char *str, int *j)
{
	int		i;
	char	quote;
	char	*cpy;

	i = 0;
	while (str[i] && ft_check_whitespaces(str[i]) == FALSE)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
		}
		if (str[i])
			i++;
	}
	*j += i;
	cpy = ft_strdup_t(data, str, i);
	return (cpy);
}

char	**ft_split_token(t_data *data, char *str, char **params, int count)
{
	int		i;
	int		j;
	char	**tmp;

	i = ft_count_params(params) + count;
	j = 0;
	tmp = malloc(sizeof(char *) * (i + 1));
	ft_check_malloc(data, tmp);
	i = 0;
	while (params && params[i])
	{
		tmp[i] = ft_strdup_t(data, params[i], -1);
		i++;
	}
	while (str && str[j])
	{
		while (str[j] && ft_check_whitespaces(str[j]) == TRUE)
			j++;
		if (str[j] != '\0')
			tmp[i++] = ft_cpy_param(data, str + j, &j);
	}
	if (params)
		ft_clear_arr(params);
	tmp[i] = NULL;
	return (tmp);
}
