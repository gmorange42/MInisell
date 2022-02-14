/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:50:36 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:50:40 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_error(char *ope)
{
	char	*error;

	error = "minishell: syntax error near unexpected token `";
	write(2, error, ft_strlen(error));
	write(2, ope, ft_strlen(ope));
	write(2, "'\n", 2);
	return (FALSE);
}

int	ft_skip_quotes(char *str, int *ret)
{
	int		i;
	char	quote;

	i = 1;
	quote = str[0];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		return (i + 1);
	else
	{
		write(2, "Error: unclosed quotes\n", 23);
		*ret = FALSE;
	}
	return (1);
}

int	ft_skip_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_check_whitespaces(str[i]) == TRUE)
		i++;
	return (i);
}
