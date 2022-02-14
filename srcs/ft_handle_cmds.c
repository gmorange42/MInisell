/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:57:49 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 14:28:52 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirection(t_data *data, t_elem *elem, t_token *token)
{
	while (token && elem->redirect == TRUE)
	{
		if (ft_strncmp(token->new_str, "<", -1) == TRUE)
			ft_redirect_input(elem, token);
		else if (ft_strncmp(token->new_str, ">", -1) == TRUE)
			ft_redirect_output(elem, token, 1);
		else if (ft_strncmp(token->new_str, ">>", -1) == TRUE)
			ft_redirect_output(elem, token, 2);
		token = token->next;
	}
	if (elem->redirect == FALSE && data->count_pipes > 0)
	{
		data->error = 1;
		ft_free_child(data);
	}
}

static void	ft_waitpid(t_data *data)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < data->count_pids)
	{
		waitpid(data->pids[i], &(data->status), 0);
		ft_exit_status(data);
		if (data->error == 130 && flag == 0)
		{
			write(1, "\n", 1);
			flag = 1;
		}
		else if (i == data->count_pids - 1)
		{
			if (data->error == 131)
				write(1, "Quit (core dumped)\n", 19);
		}
		i++;
	}
}

static void	ft_check_cmds(t_data *data)
{
	t_elem	*elem;

	elem = data->first_elem;
	while (elem)
	{
		if (elem->cmd && !elem->path)
			ft_cmd_not_found(data, elem);
		elem = elem->next;
	}
}

static void	ft_count_pipes_pids(t_data *data)
{
	data->count_pipes = ft_count_pipes(data);
	data->count_pids = ft_count_pids(data);
	if (data->count_pipes > 0)
	{
		data->pipes = malloc(sizeof(int [2]) * data->count_pipes);
		ft_check_malloc(data, data->pipes);
	}
	data->pids = malloc(sizeof(int) * data->count_pids);
	ft_check_malloc(data, data->pids);
}

void	ft_handle_cmds(t_data *data)
{
	ft_count_pipes_pids(data);
	ft_redirect_heredoc(data, data->first_elem);
	if (g_global == 130)
		return ;
	ft_check_cmds(data);
	if (ft_first_cmd(data, data->first_elem) == FALSE)
		return ;
	if (data->count_pids > 2)
		ft_inter_cmds(data, data->first_elem->next);
	if (data->count_pids > 1)
		ft_last_cmd(data, data->first_elem);
	if (data->count_pipes < 1 && data->first_elem->builtin)
		return ;
	data->sig.sa_handler = SIG_IGN;
	ft_signals(data);
	ft_waitpid(data);
	data->sig.sa_handler = &ft_sig_main;
	ft_signals(data);
}
