/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:52:21 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:52:24 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_status(t_data *data)
{
	int	exit_status;

	if (WIFEXITED(data->status))
	{
		exit_status = WEXITSTATUS(data->status);
		data->error = exit_status;
	}
	if (WIFSIGNALED(data->status))
	{
		exit_status = WTERMSIG(data->status);
		data->error = exit_status + 128;
	}
}
