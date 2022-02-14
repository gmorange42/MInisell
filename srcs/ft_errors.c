/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:51:45 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 14:22:29 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_malloc(t_data *data, void *elem)
{
	char	*str;

	str = "Error\nMalloc failed\n";
	if (!elem)
	{
		write(2, str, ft_strlen(str));
		data->error = 1;
		ft_free(data);
	}
}

void	ft_check_open(int fd, char *str, char *old_str)
{
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		if (!str || (str && !str[0]))
		{
			write(2, old_str, ft_strlen(old_str));
			write(2, ": ambiguous redirect\n", 21);
		}
		else
		{
			write(2, str, ft_strlen(str));
			write(2, ": ", 2);
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "\n", 1);
		}
	}
}

void	ft_strerror(t_data *data, char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	data->error = 1;
}
