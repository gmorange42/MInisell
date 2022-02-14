/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:51:26 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 14:29:37 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_last_param_echo(char *str, int flag)
{
	write(1, str, ft_strlen(str));
	if (flag == 0)
		write(1, "\n", 1);
}

static void	ft_check_option_echo(char **params, int *i, int *flag)
{
	int	j;

	if (*i == 1)
	{
		while (params && params[*i] && params[*i][0] == '-')
		{
			j = 1;
			while (params[*i][j] == 'n')
				j++;
			if (params[*i][j] == '\0' && params[*i][j - 1] == 'n')
			{
				*flag = 1;
				*i += 1;
			}
			else
				return ;
		}
	}
}

static int	ft_check_params_echo(t_data *data, t_elem *elem)
{
	if (elem && elem->params && !elem->params[1])
	{
		data->error = 0;
		write(1, "\n", 1);
		return (FALSE);
	}
	return (TRUE);
}

void	ft_echo(t_data *data, t_elem *elem)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	j = 1;
	flag = 0;
	if (ft_check_params_echo(data, elem) == FALSE)
		return ;
	while (elem && elem->params && elem->params[i] && elem->params[i + 1])
	{
		if (i == 1 && elem->params[i][0] == '-')
			ft_check_option_echo(elem->params, &i, &flag);
		if (elem->params[i] && elem->params[i + 1])
		{
			write(1, elem->params[i], ft_strlen(elem->params[i]));
			write(1, " ", 1);
			i += 1;
		}
	}
	ft_check_option_echo(elem->params, &i, &flag);
	ft_last_param_echo(elem->params[i], flag);
	data->error = 0;
	if (data->count_pipes > 0)
		ft_free_child(data);
}
