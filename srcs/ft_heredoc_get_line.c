/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_get_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:59:52 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 14:33:48 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_error_heredoc(char *str)
{
	char	*error;

	error = "minishell: warning: here-document delimited \
by end-of-file (wanted `";
	write(1, error, ft_strlen(error));
	write(1, str, ft_strlen(str));
	write(1, "')\n", 3);
}

static void	ft_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		g_global = 130;
	}
	else if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

static void	ft_write_heredoc(t_data *data, char *input, int heredoc, int expand)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '$' && expand == TRUE)
			i += ft_expand_heredoc(data, heredoc, &input[i]);
		else
		{
			write(heredoc, &input[i], 1);
			i++;
		}
	}
	write(heredoc, "\n", 1);
}

static int	ft_quit_heredoc(char *input)
{
	free(input);
	input = NULL;
	return (TRUE);
}

int	ft_get_line(t_data *data, char **str, int heredoc)
{
	char	*input;
	int		expand;

	input = ft_strdup_t(data, "\0", -1);
	expand = ft_check_heredoc(data, str);
	while (input)
	{
		data->sig.sa_handler = &ft_sig_heredoc;
		ft_signals(data);
		free(input);
		input = NULL;
		input = readline("> ");
		if (!input && g_global != 130)
			ft_print_error_heredoc(*str);
		if (!input && g_global == 130)
			return (FALSE);
		else
		{
			if (input && ft_strncmp(input, *str, -1) == TRUE)
				return (ft_quit_heredoc(input));
			if (input)
				ft_write_heredoc(data, input, heredoc, expand);
		}
	}
	return (TRUE);
}
