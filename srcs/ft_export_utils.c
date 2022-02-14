/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:53:18 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:21:51 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_export_error(t_data *data, char *param)
{
	data->error = 1;
	write(2, "minishell: export: `", 20);
	write(2, param, ft_strlen(param));
	write(2, "': not a valid identifier\n", 26);
	return (FALSE);
}

int	ft_find_biggest(t_data *data)
{
	int	i;
	int	biggest;

	i = 0;
	biggest = 0;
	while (data->env && data->env[i])
	{
		if (ft_cmp_env(data->env[i], data->env[biggest]) > 0)
			biggest = i;
		i++;
	}
	return (biggest);
}

int	ft_find_smallest(t_data *data, int smallest, int biggest, int flag)
{
	int	i;
	int	old_smallest;

	i = 0;
	if (flag != 0)
		old_smallest = smallest;
	while (data->env && data->env[i])
	{
		if (flag == 0)
		{
			if (ft_cmp_env(data->env[i], data->env[smallest]) < 0)
				smallest = i;
		}
		else
		{
			if (ft_cmp_env(data->env[i], data->env[old_smallest]) > 0 && \
					ft_cmp_env(data->env[i], data->env[biggest]) < 0)
				biggest = i;
		}
		i++;
	}
	if (flag == 0)
		return (smallest);
	return (biggest);
}

int	ft_cmp_env(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '=')
		return (-1);
	if (s2[i] == '=')
		return (1);
	return (s1[i] - s2[i]);
}

void	ft_print_export(char *str)
{
	int	i;
	int	equal;

	i = 0;
	equal = FALSE;
	write(1, "export ", 7);
	while (str && str[i])
	{
		if (str[i] == '=' && equal == FALSE)
		{
			equal = TRUE;
			write(1, &str[i], 1);
			write(1, "\"", 1);
		}
		else
			write(1, &str[i], 1);
		i++;
	}
	if (equal == TRUE)
		write(1, "\"", 1);
	write(1, "\n", 1);
}
