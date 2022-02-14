/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:50:27 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 14:49:17 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_syntax_pipe(char *str)
{
	int	i;

	i = 1;
	if (ft_check_whitespaces(str[i]) == TRUE)
		i += ft_skip_whitespaces(&str[i]);
	if (str[i] == '|')
		return (ft_syntax_error("|"));
	if (!str[i])
		return (ft_syntax_error("newline"));
	return (TRUE);
}

static int	ft_check_error_syntax_redirect(char *str, int i)
{
	if (str[i] == '<')
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (ft_syntax_error("<<"));
		else
			return (ft_syntax_error("<"));
	}
	if (str[i] == '>')
	{
		if (str[i] == '>' && str[i + 1] == '>')
			return (ft_syntax_error(">>"));
		else
			return (ft_syntax_error(">"));
	}
	return (FALSE);
}

static int	ft_check_syntax_redirect(char *str)
{
	int		i;
	char	redirect;

	i = 1;
	redirect = str[0];
	if (str[1] == redirect)
		i++;
	else if (ft_check_whitespaces(str[i]) == TRUE)
		i += ft_skip_whitespaces(&str[i]);
	if (!str[i])
		return (ft_syntax_error("newline"));
	if (str[i] == '|')
		return (ft_syntax_error("|"));
	if (str[i] == '<' || str[i] == '>')
		return (ft_check_error_syntax_redirect(str, i));
	return (TRUE);
}

static void	ft_check_ret(t_data *data, int ret)
{
	if (ret == TRUE)
	{
		ft_check_env_var(data);
		ft_find_cmds(data);
	}
}

int	ft_check_syntax(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	ret = TRUE;
	if (data->input[0] == '|')
		return (ft_syntax_error("|"));
	while (data->input && data->input[i] && ret == TRUE)
	{
		if (data->input[i] == '\'' || data->input[i] == '"')
			i += ft_skip_quotes(&data->input[i], &ret);
		else if (ft_check_whitespaces(data->input[i]) == TRUE)
			i += ft_skip_whitespaces(&data->input[i]);
		else
		{
			if (data->input[i] == '|')
				ret = ft_check_syntax_pipe(&data->input[i]);
			else if (data->input[i] == '<' || data->input[i] == '>')
				ret = ft_check_syntax_redirect(&data->input[i]);
			i++;
		}
	}
	ft_check_ret(data, ret);
	return (TRUE);
}
