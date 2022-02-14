/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:54:07 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:22:24 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_set_null(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	ft_clear_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_free_pipes_pids(t_data *data)
{
	free(data->pipes);
	data->pipes = NULL;
	free(data->pids);
	data->pids = NULL;
}

int	ft_free(t_data *data)
{
	int	error;

	error = data->error;
	ft_clear_list(data);
	ft_clear_arr(data->builtins);
	ft_clear_arr(data->paths);
	ft_free_pipes_pids(data);
	close(data->cpy_stdin);
	close(data->cpy_stdout);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	free(data->input);
	data->input = NULL;
	ft_clear_arr(data->env);
	rl_clear_history();
	if (error != 0)
	{
		free(data);
		exit(error);
	}
	free(data);
	data = NULL;
	return (0);
}

int	ft_free_child(t_data *data)
{
	int	error;

	error = data->error;
	ft_clear_list(data);
	ft_clear_arr(data->builtins);
	ft_clear_arr(data->paths);
	ft_free_pipes_pids(data);
	close(data->cpy_stdin);
	close(data->cpy_stdout);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	rl_clear_history();
	free(data->input);
	data->input = NULL;
	ft_clear_arr(data->env);
	free(data);
	exit(error);
}
