/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:02:03 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:02:31 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quotes(char *input, int *i)
{
	int		j;
	char	quote;

	j = *i;
	if (input[j] == '\'' || input[j] == '\"')
	{
		quote = input[j];
		j += 1;
		while (input[j] != quote && input[j] != '\0')
			j++;
		if (input[j] == '\0')
		{
			*i += 1;
			return (*i);
		}
		if (input[j] == quote)
		{
			j += 1;
			*i = j;
		}
	}
	return (0);
}

static int	ft_check_common_char(t_data *data, char *input, int *i)
{
	int	j;

	j = *i;
	while (input && input[j] && input[j] != '|')
	{
		ft_check_quotes(input, &j);
		if (input[j] != '\0' && input[j] != '|' && \
			input[j] != '\'' && input[j] != '"')
			j++;
	}
	if (j != *i)
		ft_cpy_elem(data, input, *i, j);
	*i = j;
	return (0);
}

static int	ft_check_pipe(t_data *data, char *input, int *i)
{
	int		j;

	j = *i;
	if (input[j] == '|')
	{
		j += 1;
		ft_cpy_elem(data, input, *i, j);
	}
	*i = j;
	return (0);
}

int	ft_parsing(t_data *data)
{
	int	i;

	i = 0;
	while (data->input && data->input[i])
	{
		ft_check_pipe(data, data->input, &i);
		ft_check_common_char(data, data->input, &i);
	}
	return (0);
}
