/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:53:48 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 14:21:58 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fd_first_cmd(t_data *data, t_elem *elem)
{
	t_token	*token;

	token = elem->first_token;
	if (data->count_pipes > 0)
	{	
		close(data->pipes[0][0]);
		dup2(data->pipes[0][1], STDOUT_FILENO);
		close(data->pipes[0][1]);
	}
	ft_redirection(data, elem, token);
}

int	ft_check_redirection(t_data *data, t_elem *elem)
{
	if (elem->redirect == FALSE)
	{
		data->error = 1;
		dup2(data->cpy_stdin, STDIN_FILENO);
		dup2(data->cpy_stdout, STDOUT_FILENO);
		return (FALSE);
	}
	ft_handle_builtins(data, elem);
	dup2(data->cpy_stdin, STDIN_FILENO);
	dup2(data->cpy_stdout, STDOUT_FILENO);
	return (TRUE);
}

int	ft_first_cmd(t_data *data, t_elem *first)
{
	t_elem	*elem;

	elem = first;
	if (data->count_pipes < 1 && elem->builtin)
	{
		ft_redirection(data, elem, elem->first_token);
		if (ft_check_redirection(data, elem) == FALSE)
			return (FALSE);
		else
			return (TRUE);
	}
	if (data->count_pipes > 0)
	{
		if (pipe(data->pipes[0]) == -1)
			ft_free(data);
	}
	data->pids[0] = fork();
	if (data->pids[0] == -1)
		ft_free(data);
	else if (data->pids[0] == 0)
	{
		ft_fd_first_cmd(data, first);
		ft_exec(data, first);
	}
	return (TRUE);
}
