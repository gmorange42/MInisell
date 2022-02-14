/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:58:51 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:59:03 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_path(t_data *data, t_elem *elem)
{
	int	i;

	i = 0;
	if (elem->cmd[0] == '\0')
		return ;
	while (data->paths && data->paths[i])
	{
		elem->path = ft_strjoin(data, data->paths[i], elem->cmd, 2);
		if (access(elem->path, X_OK) == 0)
			return ;
		free(elem->path);
		elem->path = NULL;
		i++;
	}
}

static int	ft_absolute_path(t_data *data, t_elem *elem)
{
	int	i;

	i = 0;
	if (access(elem->cmd, X_OK) == 0)
	{
		elem->path = ft_strdup_t(data, elem->cmd, -1);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_handle_path(t_data *data, t_elem *elem)
{
	int	i;

	i = 0;
	if (ft_absolute_path(data, elem) == FALSE)
	{
		while (data->env && data->env[i])
		{
			if (ft_strncmp("PATH=", data->env[i], 5) == TRUE)
			{
				if (data->paths)
					ft_clear_arr(data->paths);
				data->paths = ft_split_path(data, data->env[i]);
				ft_check_path(data, elem);
				return ;
			}
			i++;
		}
	}
}
