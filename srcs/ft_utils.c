/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:19:56 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:20:03 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (n >= 0)
	{
		while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i] && i + 1 < n)
			i++;
	}
	else
	{
		while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
			i++;
	}
	if (s1[i] != s2[i])
		return (FALSE);
	return (TRUE);
}

int	ft_check_whitespaces(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || \
		c == '\v' || c == '\f' || c == ' ')
		return (TRUE);
	return (FALSE);
}

char	*ft_strjoin(t_data *data, char *s1, char *s2, int flag)
{
	int		i;
	int		j;
	char	*cpy;

	i = ft_strlen(s1) + ft_strlen(s2);
	cpy = malloc(sizeof(char) * (i + flag));
	ft_check_malloc(data, cpy);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	if (flag == 2)
	{
		cpy[i] = '/';
		i++;
	}
	while (s2 && s2[j])
		cpy[i++] = s2[j++];
	cpy[i] = '\0';
	return (cpy);
}
