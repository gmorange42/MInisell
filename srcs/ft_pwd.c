/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:16:37 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:16:40 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data, int flag)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) == 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		data->error = 1;
		if (data->count_pipes > 0)
			ft_free_child(data);
		else
			return ;
	}
	if (flag == 0)
	{
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
		return ;
	}
	data->pwd = ft_strdup_t(data, pwd, -1);
}
