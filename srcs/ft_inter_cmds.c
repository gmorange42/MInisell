/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inter_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:00:39 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:01:31 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fd_inter_cmds(t_data *data, t_elem *elem, int i)
{
	t_token	*token;

	token = elem->first_token;
	close(data->pipes[i - 1][1]);
	dup2(data->pipes[i - 1][0], STDIN_FILENO);
	close(data->pipes[i - 1][0]);
	close(data->pipes[i][0]);
	dup2(data->pipes[i][1], STDOUT_FILENO);
	close(data->pipes[i][1]);
	ft_redirection(data, elem, token);
}

static void	ft_close_previous_parents_pipe(t_data *data, int i)
{
	close(data->pipes[i - 1][0]);
	close(data->pipes[i - 1][1]);
}

void	ft_inter_cmds(t_data *data, t_elem *first)
{
	int		i;
	t_elem	*elem;

	i = 1;
	elem = first;
	while (elem && elem->next)
	{
		if (elem->str[0] != '|')
		{
			if (pipe(data->pipes[i]) == -1)
				ft_free(data);
			data->pids[i] = fork();
			if (data->pids[i] == -1)
				ft_free(data);
			else if (data->pids[i] != 0)
				ft_close_previous_parents_pipe(data, i);
			else
			{
				ft_fd_inter_cmds(data, elem, i);
				ft_exec(data, elem);
			}
			i++;
		}
		elem = elem->next;
	}
}
