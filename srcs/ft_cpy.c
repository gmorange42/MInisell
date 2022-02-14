/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:51:13 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:51:19 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cpy_envp(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	if (i == 0)
		return ;
	data->env = malloc(sizeof(char *) * (i + 1));
	ft_check_malloc(data, data->env);
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup_t(data, envp[i], -1);
		i++;
	}
	data->env[i] = NULL;
}

int	ft_cpy_elem(t_data *data, char *input, int i, int j)
{
	int		len;
	char	*cpy;

	len = j - i;
	cpy = malloc(sizeof(char) * (len + 1));
	ft_check_malloc(data, cpy);
	len = 0;
	while (i < j)
		cpy[len++] = input[i++];
	cpy[len] = '\0';
	ft_add_back_elem(data, cpy);
	return (0);
}

int	ft_cpy_token(t_data *data, t_elem *elem, int i, int j)
{
	int		len;
	char	*cpy;

	len = j - i;
	cpy = malloc(sizeof(char) * (len + 1));
	ft_check_malloc(data, cpy);
	len = 0;
	while (i < j)
		cpy[len++] = elem->str[i++];
	cpy[len] = '\0';
	ft_add_back_token(data, elem, cpy);
	return (0);
}
