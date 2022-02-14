/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_t.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:20:07 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:20:11 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_t(t_data *data, char *str, int len)
{
	int		i;
	char	*cpy;

	i = 0;
	if (len > 0)
		cpy = malloc(sizeof(char) * (len + 1));
	else
	{
		len = ft_strlen(str);
		cpy = malloc(sizeof(char) * (len + 1));
	}
	ft_check_malloc(data, cpy);
	while (i < len)
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin_t(t_data *data, char *s1, char *s2)
{
	int		i;
	int		j;
	char	*cpy;

	i = ft_strlen(s1) + ft_strlen(s2);
	cpy = malloc(sizeof(char) * (i + 1));
	ft_check_malloc(data, cpy);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		cpy[i++] = s2[j++];
	cpy[i] = '\0';
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	return (cpy);
}
