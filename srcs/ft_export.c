/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:53:11 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 13:44:49 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_env_export(t_data *data, int i, int j, char *param)
{
	while (data->env && data->env[j])
	{
		if ((param[i] == '=' && \
		ft_strncmp(param, data->env[j], i + 1) == TRUE) || \
		(ft_strncmp(param, data->env[j], i) == TRUE && \
		param[i] == '=' && !data->env[j][i]))
		{
			free(data->env[j]);
			data->env[j] = NULL;
			data->env[j] = ft_strdup_t(data, param, -1);
			return (FALSE);
		}
		if (param[i] != '=' && ft_strncmp(param, data->env[j], i) == TRUE \
		&& data->env[j][i] == '=')
			return (FALSE);
		j++;
	}
	return (TRUE);
}

static int	ft_check_export(t_data *data, char *param)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (param && (param[0] < 65 || (param[0] > 90 && param[0] < 97) || \
				param[0] > 122) && param[0] != '_')
		return (ft_print_export_error(data, param));
	while (param && param[i] && \
		((param[i] >= '0' && param[i] <= '9') || \
		(param[i] >= 'a' && param[i] <= 'z') || \
		(param[i] >= 'A' && param[i] <= 'Z') || \
		param[i] == '_'))
		i++;
	if (param[i] != '\0' && param[i] != '=')
		return (ft_print_export_error(data, param));
	return (ft_check_env_export(data, i, j, param));
}

static void	ft_new_env_tab(t_data *data, char *new_env_var)
{
	int		i;
	char	**new_env_tab;

	i = 0;
	while (data->env && data->env[i])
		i++;
	new_env_tab = malloc(sizeof(char *) * (i + 2));
	ft_check_malloc(data, new_env_tab);
	i = 0;
	while (data->env && data->env[i])
	{
		new_env_tab[i] = ft_strdup_t(data, data->env[i], -1);
		i++;
	}
	new_env_tab[i++] = ft_strdup_t(data, new_env_var, -1);
	new_env_tab[i] = NULL;
	if (data->env)
		ft_clear_arr(data->env);
	data->env = new_env_tab;
}

static void	ft_export_env(t_data *data)
{
	int	smallest;
	int	biggest;
	int	flag;

	flag = 0;
	biggest = ft_find_biggest(data);
	smallest = 0;
	smallest = ft_find_smallest(data, smallest, biggest, flag);
	if (data->env && ft_count_params(data->env) == 1)
	{
		ft_print_export(data->env[smallest]);
		return ;
	}
	while (data->env && \
	ft_cmp_env(data->env[smallest], data->env[biggest]) != 0)
	{
		smallest = ft_find_smallest(data, smallest, biggest, flag);
		ft_print_export(data->env[smallest]);
		flag = 1;
	}
}

void	ft_export(t_data *data, t_elem *elem)
{
	int	i;

	i = 1;
	if (elem && elem->params && !elem->params[1])
	{
		if (data->env && data->env[0])
			ft_export_env(data);
		return ;
	}
	while (elem && elem->params && elem->params[i])
	{
		if (ft_check_export(data, elem->params[i]) == TRUE)
			ft_new_env_tab(data, elem->params[i]);
		i++;
	}
	if (data->count_pipes > 0)
		ft_free_child(data);
}
