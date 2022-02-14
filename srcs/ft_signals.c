/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:31:33 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:44:26 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_main(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global = 130;
	}
	else if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

void	ft_signals(t_data *data)
{
	data->sig.sa_flags = 0;
	memset(&(data->sig.sa_mask), '\0', sizeof(data->sig.sa_mask));
	sigaction(SIGINT, &(data->sig), NULL);
	sigaction(SIGQUIT, &(data->sig), NULL);
}
