/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:51:37 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:51:41 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->env && data->env[i])
	{
		j = 0;
		while (data->env[i][j] && data->env[i][j] != '=')
			j++;
		if (data->env[i][j])
		{
			write(1, data->env[i], ft_strlen(data->env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	if (data->count_pipes > 0)
		ft_free_child(data);
}
