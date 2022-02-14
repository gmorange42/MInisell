/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:52:29 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:44:10 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cpy_rest(t_data *data, t_token *token, char *str, int pos)
{
	int	len;

	len = ft_strlen(str) - pos;
	token->cpy = ft_strdup_t(data, str + pos, len);
	token->new_str = ft_strjoin_t(data, token->new_str, token->cpy);
	free(token->cpy);
	token->cpy = NULL;
}

static char	*ft_get_var_value(t_data *data, char *var_name, int len)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = NULL;
	while (data->env && data->env[i])
	{
		if (ft_strncmp(data->env[i], var_name, len) == TRUE)
		{
			cpy = ft_strdup_t(data, data->env[i] + len, -1);
			break ;
		}
		i++;
	}
	return (cpy);
}

static char	*ft_get_var_name(t_data *data, char *str, int len)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = malloc(sizeof(char) * (len + 1));
	ft_check_malloc(data, var_name);
	while (i < len - 1)
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i++] = '=';
	var_name[i] = '\0';
	return (var_name);
}

static void	ft_get_var(t_data *data, t_token *token, char *str, int tab[2])
{
	char	*var_name;

	var_name = ft_get_var_name(data, str, tab[1]);
	if (ft_strncmp(var_name, "?=", -1) == TRUE)
	{
		data->last_status = ft_itoa(data, data->error);
		token->new_str = ft_strjoin_t(data, token->new_str, data->last_status);
		free(data->last_status);
		data->last_status = NULL;
	}
	else
	{
		token->env_var = ft_get_var_value(data, var_name, tab[1]);
		token->new_str = ft_strjoin_t(data, token->new_str, token->env_var);
		free(token->env_var);
		token->env_var = NULL;
	}
	free(var_name);
	var_name = NULL;
}

int	ft_expand_var(t_data *data, t_token *token, char *str)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	pos = 0;
	while (i < token->tab_len)
	{
		if (pos != token->tab[i][0])
		{
			j = token->tab[i][0] - pos;
			token->cpy = ft_strdup_t(data, str + pos, j);
			pos += j;
			token->new_str = ft_strjoin_t(data, token->new_str, token->cpy);
			free(token->cpy);
			token->cpy = NULL;
		}
		ft_get_var(data, token, str + pos + 1, token->tab[i]);
		pos += token->tab[i][1];
		i++;
	}
	ft_cpy_rest(data, token, str, pos);
	return (0);
}
