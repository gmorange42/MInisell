/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:26:30 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 16:06:18 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global = 0;

void	ft_unlink_heredoc(t_data *data)
{
	char	*path;
	char	*nbr;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (ret == 0)
	{
		nbr = ft_itoa(data, i);
		path = ft_strjoin(data, "/tmp/heredoc", nbr, 1);
		ret = unlink(path);
		free(nbr);
		free(path);
		i++;
	}
}

void	ft_reset(t_data *data)
{
	ft_unlink_heredoc(data);
	ft_clear_list(data);
	ft_free_pipes_pids(data);
	data->quote = 0;
	free(data->input);
	data->input = NULL;
}

void	ft_check_history(t_data *data)
{
	if (data->input[0] != '\0')
		add_history(data->input);
}

int	ft_check_input(t_data *data)
{
	if (g_global != 0)
		data->error = g_global;
	g_global = 0;
	if (data->input == NULL)
	{
		write(1, "exit\n", 5);
		ft_free(data);
		exit (0);
	}
	else if (data->input[0] == '\0')
	{
		free(data->input);
		data->input = NULL;
		return (FALSE);
	}
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1)
		return (0);
	(void)argv;
	data = ft_init_data();
	ft_cpy_envp(data, envp);
	ft_set_builtins(data);
	while (1)
	{
		data->sig.sa_handler = &ft_sig_main;
		ft_signals(data);
		data->input = readline("minishell$ ");
		if (ft_check_input(data) == TRUE)
		{
			ft_parsing(data);
			ft_check_history(data);
			ft_check_syntax(data);
			ft_reset(data);
		}
	}
	ft_free(data);
	return (0);
}
