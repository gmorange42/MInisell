/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:58:24 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:58:36 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_back_elem(t_data *data, char *str)
{
	t_elem	*new;
	t_elem	*first;

	new = malloc(sizeof(t_elem));
	ft_check_malloc(data, new);
	ft_init_elem(new);
	new->str = str;
	first = NULL;
	if (!data->first_elem)
	{
		data->first_elem = new;
		new->prev = NULL;
	}
	else
	{
		first = data->first_elem;
		while (first->next)
			first = first->next;
		first->next = new;
		new->prev = first;
	}
}

void	ft_add_back_token(t_data *data, t_elem *elem, char *str)
{
	t_token	*new;
	t_token	*first;

	new = malloc(sizeof(t_token));
	ft_check_malloc(data, new);
	ft_init_token(new);
	new->str = str;
	first = NULL;
	if (!elem->first_token)
	{
		elem->first_token = new;
		new->prev = NULL;
	}
	else
	{
		first = elem->first_token;
		while (first->next)
			first = first->next;
		first->next = new;
		new->prev = first;
	}
}

int	ft_get_size(void *list, int flag)
{
	int		i;
	t_elem	*first_elem;
	t_token	*first_token;

	i = 0;
	first_elem = NULL;
	first_token = NULL;
	if (flag == 1)
		first_elem = list;
	if (flag == 2)
		first_token = list;
	while (first_elem || first_token)
	{
		i++;
		if (first_elem)
			first_elem = first_elem->next;
		if (first_token)
			first_token = first_token->next;
	}
	return (i);
}

void	ft_clear_tokens(t_token *token)
{
	while (token)
	{
		ft_free_set_null(token->str);
		ft_free_set_null(token->cpy);
		ft_free_set_null(token->env_var);
		ft_free_set_null(token->new_str);
		free(token->tab);
		free(token->prev);
		token->prev = NULL;
		if (token->next == NULL)
		{
			free(token);
			token = NULL;
		}
		else
			token = token->next;
	}
}

void	ft_clear_list(t_data *data)
{
	while (data->first_elem)
	{
		ft_clear_tokens(data->first_elem->first_token);
		ft_free_set_null(data->first_elem->str);
		ft_free_set_null(data->first_elem->builtin);
		ft_free_set_null(data->first_elem->cmd);
		ft_free_set_null(data->first_elem->path);
		ft_clear_arr(data->first_elem->params);
		free(data->first_elem->prev);
		data->first_elem->prev = NULL;
		if (data->first_elem->next == NULL)
		{
			free(data->first_elem);
			data->first_elem = NULL;
		}
		else
			data->first_elem = data->first_elem->next;
	}
	free(data->first_elem);
	data->first_elem = NULL;
}
