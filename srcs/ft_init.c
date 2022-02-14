/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:00:02 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:00:26 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_error_malloc(t_data *data, int flag)
{
	if (flag == 1)
		if (data)
			free(data);
	write(2, "Error\nMalloc failed\n", 20);
	exit(1);
}

t_data	*ft_init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_error_malloc(data, 0);
	data->first_elem = NULL;
	data->env = NULL;
	data->input = NULL;
	data->home = getenv("HOME");
	data->pwd = NULL;
	data->builtins = malloc(sizeof(char *) * (7 + 1));
	if (!data->builtins)
		ft_error_malloc(data, 1);
	data->paths = NULL;
	data->quote = '\0';
	data->count_pipes = 0;
	data->count_pids = 0;
	data->cpy_stdin = dup(STDIN_FILENO);
	data->cpy_stdout = dup(STDOUT_FILENO);
	data->pipes = NULL;
	data->pids = NULL;
	data->status = 0;
	data->last_status = NULL;
	data->error = 0;
	return (data);
}

void	ft_set_builtins(t_data *data)
{
	data->builtins[0] = ft_strdup_t(data, "echo", -1);
	data->builtins[1] = ft_strdup_t(data, "cd", -1);
	data->builtins[2] = ft_strdup_t(data, "pwd", -1);
	data->builtins[3] = ft_strdup_t(data, "export", -1);
	data->builtins[4] = ft_strdup_t(data, "unset", -1);
	data->builtins[5] = ft_strdup_t(data, "env", -1);
	data->builtins[6] = ft_strdup_t(data, "exit", -1);
	data->builtins[7] = NULL;
}

void	ft_init_elem(t_elem *elem)
{
	elem->str = NULL;
	elem->first_token = NULL;
	elem->redirect = TRUE;
	elem->heredoc = -1;
	elem->builtin = NULL;
	elem->cmd = NULL;
	elem->path = NULL;
	elem->params = NULL;
	elem->prev = NULL;
	elem->next = NULL;
}

void	ft_init_token(t_token *token)
{
	token->str = NULL;
	token->tab = NULL;
	token->tab_len = 0;
	token->cpy = NULL;
	token->env_var = NULL;
	token->new_str = NULL;
	token->prev = NULL;
	token->next = NULL;
}
