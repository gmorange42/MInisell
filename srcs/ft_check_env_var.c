/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_env_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:50:16 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:44:00 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_add_to_tab(t_data *data, t_token *token, int start, int end)
{
	int	i;
	int	(*new_tab)[2];

	i = 0;
	token->tab_len += 1;
	new_tab = malloc(sizeof(int [2]) * token->tab_len);
	ft_check_malloc(data, new_tab);
	while (i < token->tab_len)
	{
		if (token->tab_len > 1 && i < token->tab_len - 1)
		{
			new_tab[i][0] = token->tab[i][0];
			new_tab[i][1] = token->tab[i][1];
		}
		i++;
	}
	new_tab[token->tab_len - 1][0] = start;
	new_tab[token->tab_len - 1][1] = end;
	if (token->tab)
		free(token->tab);
	token->tab = new_tab;
}

static void	ft_get_pos_len(t_data *data, t_token *token, int count, int start)
{
	while (count > 0 && token->str[start])
	{
		while (token->str[start] && token->str[start] != '$')
			start++;
		if (token->str[start] && token->str[start + 1] \
			&& token->str[start + 1] == '$')
			start += 1;
		else if (token->str[start] == '$')
		{
			ft_add_to_tab(data, token, start, \
				ft_count_var_len(token->str + start));
			count--;
		}
		if (token->str[start])
			start++;
	}
}

static int	ft_handle_quotes(t_data *data, t_token *token, char *str, int start)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	if (start == -1)
	{
		while (str && str[i] && str[i] != '\'')
			i++;
		if (str[i] == '\'')
			return (i);
		else
			return (0);
	}
	while (str && str[i] && str[i] != '"')
	{
		if (str[i] == '$')
		{
			if (ft_count_var_len(&str[i]) > 1)
				count += 1;
		}
		i++;
	}
	ft_get_pos_len(data, token, count, start);
	return (i);
}

static void	ft_count_env_var(t_data *data, t_token *token)
{
	int	i;

	i = 0;
	while (token && token->str && token->str[i])
	{
		if (token->str[i] == '$')
		{
			if (token->str[i + 1] == '$' || !token->str[i + 1] || \
			!((token->str[i + 1] >= '0' && token->str[i + 1] <= '9') || \
			(token->str[i + 1] >= 'a' && token->str[i + 1] <= 'z') || \
			(token->str[i + 1] >= 'A' && token->str[i + 1] <= 'Z') || \
			(token->str[i + 1] == '_') || token->str[i + 1] == '?' || \
			token->str[i + 1] == '\'' || token->str[i + 1] == '"'))
				i += 1;
			else
				ft_add_to_tab(data, token, i, ft_count_var_len(token->str + i));
		}
		if (token->str[i] == '\'')
			i += ft_handle_quotes(data, token, token->str + i, -1);
		if (token->str[i] == '"')
			i += ft_handle_quotes(data, token, token->str + i, i + 1);
		if (token->str[i])
			i += 1;
	}
}

void	ft_check_env_var(t_data *data)
{
	t_elem	*elem;
	t_token	*token;

	elem = data->first_elem;
	while (elem)
	{
		ft_split_elem(data, elem, elem->str);
		token = elem->first_token;
		while (token)
		{
			ft_count_env_var(data, token);
			if (g_global != 0)
				data->error = g_global;
			g_global = 0;
			ft_expand_var(data, token, token->str);
			token = token->next;
		}
		elem = elem->next;
	}
}
