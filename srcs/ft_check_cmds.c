/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:50:07 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:50:11 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_builtins(t_data *data, t_elem *elem)
{
	int	i;

	i = 0;
	while (data->builtins && data->builtins[i])
	{
		if (ft_strncmp(elem->cmd, data->builtins[i], -1) == TRUE)
		{
			elem->builtin = ft_strdup_t(data, elem->cmd, -1);
			free(elem->cmd);
			elem->cmd = NULL;
			return ;
		}
		i++;
	}
}

static int	ft_scan_str(t_data *data, char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_check_whitespaces(str[i]) == TRUE)
			i++;
		if (str[i] && ft_check_whitespaces(str[i]) == FALSE)
			count += 1;
		while (str[i] && ft_check_whitespaces(str[i]) == FALSE)
		{
			if (str[i] == '\'' || str[i] == '"')
			{
				data->quote = str[i++];
				while (str[i] && str[i] != data->quote)
					i++;
			}
			if (str[i])
				i++;
		}
	}
	return (count);
}

static void	ft_get_params(t_data *data, t_elem *elem, t_token *token)
{
	int		count;
	t_token	*first;

	count = 0;
	first = token;
	while (elem && first)
	{
		while (first && (first->new_str[0] == '<' || first->new_str[0] == '>'))
		{
			first = first->next;
			if (first)
				first = first->next;
		}
		if (first)
		{
			count = ft_scan_str(data, first->new_str);
			elem->params = ft_split_token(data, first->new_str, \
					elem->params, count);
			first = first->next;
		}
	}
}

static int	ft_skip_redirection(t_token **token)
{
	while (*token && \
			(ft_strncmp((*token)->new_str, "<", -1) == TRUE || \
			ft_strncmp((*token)->new_str, "<<", -1) == TRUE || \
			ft_strncmp((*token)->new_str, ">", -1) == TRUE || \
			ft_strncmp((*token)->new_str, ">>", -1) == TRUE))
	{
		*token = (*token)->next;
		if (*token)
			*token = (*token)->next;
		else
			return (FALSE);
	}
	if (*token)
		return (TRUE);
	return (FALSE);
}

void	ft_find_cmds(t_data *data)
{
	t_elem	*elem;
	t_token	*token;

	elem = data->first_elem;
	while (elem)
	{
		token = elem->first_token;
		if (token && token->new_str && token->new_str[0] != '|')
		{
			if (ft_skip_redirection(&token) == TRUE)
			{
				ft_get_params(data, elem, token);
				ft_supp_quotes(data, elem);
				ft_check_builtins(data, elem);
				if (elem->cmd)
					ft_handle_path(data, elem);
			}
		}
		elem = elem->next;
	}
	ft_handle_cmds(data);
}
