/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_not_found.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:50:46 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:50:47 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_not_found(t_data *data, t_elem *elem)
{
	if (elem->cmd && elem->cmd[0] == '/')
	{
		execve(elem->cmd, elem->params, data->env);
		write(2, "minishell: ", 11);
		write(2, elem->cmd, ft_strlen(elem->cmd));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		data->error = 127;
	}
	else
	{
		write(2, "minishell: ", 11);
		if (elem->cmd)
			write(2, elem->cmd, ft_strlen(elem->cmd));
		write(2, ": ", 2);
		write(2, "command not found", 17);
		write(2, "\n", 1);
		data->error = 127;
	}
}
