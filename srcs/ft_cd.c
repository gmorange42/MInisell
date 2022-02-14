/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:49:42 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:50:02 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_relative_path(t_data *data, t_elem *elem)
{
	char	*path;

	path = NULL;
	ft_pwd(data, 1);
	path = ft_strjoin(data, data->pwd, elem->params[1], 2);
	free(data->pwd);
	data->pwd = NULL;
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, elem->params[1], ft_strlen(elem->params[1]));
		write(2, ": ", 2);
		ft_strerror(data, strerror(errno));
		free(path);
		return ;
	}
	free(path);
}

static int	ft_cd_no_params(t_data *data, int count, char *home)
{
	char	*error;

	error = "minishell: cd: HOME not set\n";
	if (count == 1 && !home)
	{
		write(2, error, ft_strlen(error));
		data->error = 1;
		return (FALSE);
	}
	else if (count == 1 && home)
	{
		if (chdir(home) == -1)
			ft_strerror(data, strerror(errno));
		free(home);
		return (FALSE);
	}
	return (TRUE);
}

static void	ft_cd_home(t_data *data, t_elem *elem, int count)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	while (data->env && data->env[i])
	{
		if (ft_strncmp("HOME=", data->env[i], 5) == TRUE)
		{
			home = ft_strdup_t(data, data->env[i] + 5, -1);
			break ;
		}
		i++;
	}
	if (ft_cd_no_params(data, count, home) == FALSE)
		return ;
	free(home);
	if (elem->params[1][0] == '~')
	{
		if (data->home)
			if (chdir(data->home) == -1)
				ft_strerror(data, strerror(errno));
		return ;
	}
}

static int	ft_check_params(t_data *data, t_elem *elem)
{
	int		count;
	char	*error;

	count = ft_count_params(elem->params);
	error = "minishell: cd: too many arguments\n";
	if (elem && elem->params && count > 2)
	{
		write(2, error, ft_strlen(error));
		data->error = 1;
		return (FALSE);
	}
	if (elem && elem->params && (count == 1 || \
		(count == 2 && elem->params[1][0] == '~')))
	{
		ft_cd_home(data, elem, count);
		return (FALSE);
	}
	return (TRUE);
}

void	ft_cd(t_data *data, t_elem *elem)
{
	char	*path;

	path = NULL;
	data->error = 0;
	if (ft_check_params(data, elem) == FALSE)
		return ;
	if (elem && elem->params && elem->params[1][0] == '/')
	{
		if (chdir(elem->params[1]) == -1)
		{
			write(2, "minishell: cd: ", 15);
			write(2, elem->params[1], ft_strlen(elem->params[1]));
			write(2, ": ", 2);
			ft_strerror(data, strerror(errno));
			data->error = 1;
			return ;
		}
	}
	else
		ft_relative_path(data, elem);
}
