/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:51:04 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:51:05 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_params(char **params)
{
	int	i;

	i = 0;
	if (params)
	{
		while (params && params[i])
			i++;
		return (i);
	}
	return (0);
}

int	ft_count_var_len(char *str)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (str && str[0] && str[i] && ((str[i] >= '0' && str[i] <= '9') || \
			(str[i] >= 'a' && str[i] <= 'z') || \
			(str[i] >= 'A' && str[i] <= 'Z') || \
			(str[i] == '_') || str[i] == '?') && flag == 0)
	{
		if (str[i] == '?' || (str[i] >= '0' && str[i] <= '9'))
			flag = 1;
		i++;
	}
	return (i);
}

int	ft_count_pids(t_data *data)
{
	int	size;
	int	pids;

	size = ft_get_size(data->first_elem, 1);
	pids = size - data->count_pipes;
	return (pids);
}

int	ft_count_pipes(t_data *data)
{
	int		count;
	t_elem	*elem;

	count = 0;
	elem = data->first_elem;
	while (elem)
	{
		if (elem->str[0] == '|')
			count += 1;
		elem = elem->next;
	}
	return (count);
}
