/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:18:33 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:18:38 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_path(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		while (str[i] && str[i] == ':')
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && str[i] != ':')
			i++;
	}
	return (count);
}

static char	*ft_strdup_path(t_data *data, char *str)
{
	int		i;
	char	*cpy;

	i = 0;
	while (str && str[i] && str[i] != ':')
		i++;
	cpy = malloc(sizeof(char) * (i + 1));
	ft_check_malloc(data, cpy);
	i = 0;
	while (str && str[i] && str[i] != ':')
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**ft_split_path(t_data *data, char *str)
{
	int		i;
	int		j;
	int		count;
	char	**arr;

	i = 5;
	j = 0;
	count = ft_count_path(str);
	arr = malloc(sizeof(char *) * (count + 1));
	ft_check_malloc(data, arr);
	while (str && str[i])
	{
		while (str[i] && str[i] == ':')
			i++;
		if (str[i] != '\0')
		{
			arr[j] = ft_strdup_path(data, &str[i]);
			j += 1;
		}
		while (str[i] && str[i] != ':')
			i++;
	}
	arr[j] = NULL;
	return (arr);
}
