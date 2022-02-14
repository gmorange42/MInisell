/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:19:18 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:19:47 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_unset_error(t_data *data, char *param)
{
	data->error = 1;
	write(2, "minishell: unset: `", 20);
	write(2, param, ft_strlen(param));
	write(2, "': not a valid identifier\n", 26);
}

static void	ft_remove_env_var(t_data *data, int to_supp)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (data->env && data->env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	ft_check_malloc(data, new_env);
	i = 0;
	while (data->env && data->env[i])
	{
		if (i != to_supp)
		{
			new_env[j] = ft_strdup_t(data, data->env[i], -1);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	if (data->env)
		ft_clear_arr(data->env);
	data->env = new_env;
}

static int	ft_check_char_unset(char *str)
{
	int	i;

	i = 0;
	while (str && str[0] && str[i] && ((str[i] >= '0' && str[i] <= '9') || \
				(str[i] >= 'a' && str[i] <= 'z') || \
				(str[i] >= 'A' && str[i] <= 'Z') || \
				(str[i] == '_')))
		i++;
	return (i);
}

static void	ft_search_env_var(t_data *data, char *param)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (param && (param[0] < 65 || (param[0] > 90 && param[0] < 97) || \
	param[0] > 122) && param[0] != '_')
		return (ft_print_unset_error(data, param));
	i += ft_check_char_unset(&param[1]);
	if (param[i] != '\0')
		return (ft_print_unset_error(data, param));
	while (data->env && data->env[j])
	{
		if (ft_strncmp(param, data->env[j], i) == TRUE && \
				(data->env[j][i] == '=' || !data->env[j][i]))
		{
			ft_remove_env_var(data, j);
			return ;
		}
		j++;
	}
}

void	ft_unset(t_data *data, t_elem *elem)
{
	int	i;

	i = 1;
	if (elem->params && !elem->params[1])
		return ;
	while (elem->params && elem->params[i])
	{
		ft_search_env_var(data, elem->params[i]);
		i++;
	}
}
