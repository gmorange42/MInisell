/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:49:30 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:49:35 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_builtins(t_data *data, t_elem *elem)
{
	if (ft_strncmp(elem->builtin, "echo", -1) == TRUE)
		ft_echo(data, elem);
	if (ft_strncmp(elem->builtin, "cd", -1) == TRUE)
		ft_cd(data, elem);
	if (ft_strncmp(elem->builtin, "pwd", -1) == TRUE)
		ft_pwd(data, 0);
	if (ft_strncmp(elem->builtin, "export", -1) == TRUE)
		ft_export(data, elem);
	if (ft_strncmp(elem->builtin, "unset", -1) == TRUE)
		ft_unset(data, elem);
	if (ft_strncmp(elem->builtin, "env", -1) == TRUE)
		ft_env(data);
	if (ft_strncmp(elem->builtin, "exit", -1) == TRUE)
		ft_exit(data, elem);
	if (data->count_pipes > 0)
		ft_free_child(data);
}
