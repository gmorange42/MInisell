/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:52:00 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:52:12 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_char(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-')
		i += 1;
	if (!str[i])
		return (FALSE);
	while (str && str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	ft_check_param(t_data *data, char *param)
{
	if (ft_check_char(param) == FALSE || \
		(param[0] == '-' && ft_strlen(param) > 20) || \
		(param[0] != '-' && ft_strlen(param) > 19) || \
		ft_atol(param) == FALSE)
	{
		write(2, "minishell: exit: ", 17);
		write(2, param, ft_strlen(param));
		write(2, ": numeric argument required\n", 28);
		data->error = 2;
		return (FALSE);
	}
	return (TRUE);
}

static void	ft_too_many_arguments(t_data *data, char **params)
{
	char	*error;

	error = "minishell: exit: too many arguments\n";
	if (ft_check_char(params[1]) == FALSE)
	{
		write(2, "minishell: exit: ", 17);
		write(2, params[1], ft_strlen(params[1]));
		write(2, ": numeric argument required\n", 28);
		data->error = 2;
		if (data->count_pipes > 0)
			ft_free_child(data);
		else
			ft_free(data);
	}
	else
	{
		write(2, error, ft_strlen(error));
		data->error = 1;
	}
}

void	ft_exit(t_data *data, t_elem *elem)
{
	int		count;

	if (data->count_pipes < 1)
		write(1, "exit\n", 5);
	count = ft_count_params(elem->params);
	if (elem && elem->params && count > 2)
	{
		ft_too_many_arguments(data, elem->params);
		return ;
	}
	if (count > 1)
		if (ft_check_param(data, elem->params[1]) == TRUE)
			data->error = ft_atouc(elem->params[1]);
	if (data->count_pipes > 0)
		ft_free_child(data);
	else
	{
		ft_free(data);
		exit (0);
	}
}
