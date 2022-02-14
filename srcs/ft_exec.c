/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:51:51 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:51:53 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_data *data, t_elem *elem)
{
	if (elem->redirect == FALSE || (!elem->builtin && !elem->cmd))
	{
		if (elem->redirect == FALSE)
			data->error = 1;
		else if (!elem->builtin && !elem->cmd)
			data->error = 0;
		ft_free_child(data);
	}
	if (elem->builtin)
		ft_handle_builtins(data, elem);
	if (elem->cmd)
	{
		if (!elem->path)
			ft_free_child(data);
		if (execve(elem->path, elem->params, data->env) == -1)
		{
			write(2, elem->cmd, ft_strlen(elem->cmd));
			write(2, ": ", 2);
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "\n", 1);
			data->error = 126;
			ft_free_child(data);
		}
	}
}
