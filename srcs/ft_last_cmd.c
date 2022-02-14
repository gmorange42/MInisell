/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:01:49 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:01:51 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fd_last_cmd(t_data *data, t_elem *elem)
{
	t_token	*token;

	token = elem->first_token;
	close(data->pipes[data->count_pipes - 1][1]);
	dup2(data->pipes[data->count_pipes - 1][0], STDIN_FILENO);
	close(data->pipes[data->count_pipes - 1][0]);
	ft_redirection(data, elem, token);
}

void	ft_last_cmd(t_data *data, t_elem *first)
{
	t_elem	*elem;

	elem = first;
	if (elem->str[0] == '|')
		return ;
	while (elem && elem->next)
		elem = elem->next;
	data->pids[data->count_pids - 1] = fork();
	if (data->pids[data->count_pids - 1] != 0)
	{
		close(data->pipes[data->count_pipes - 1][0]);
		close(data->pipes[data->count_pipes - 1][1]);
	}
	else
	{
		ft_fd_last_cmd(data, elem);
		ft_exec(data, elem);
	}
}
