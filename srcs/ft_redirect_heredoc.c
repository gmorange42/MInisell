/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:16:49 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:16:54 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_heredoc(t_data *data, char **str)
{
	int		count;
	int		expand;
	char	*new_str;

	expand = TRUE;
	count = ft_count_quotes(*str);
	new_str = NULL;
	if (count > 0)
	{
		expand = FALSE;
		new_str = ft_cpy(data, *str, ft_strlen(*str) - count);
		free(*str);
		*str = new_str;
	}
	return (expand);
}

static int	ft_write_env_var(t_data *data, int fd, char **str, int len)
{
	int	i;
	int	j;

	j = len;
	i = 0;
	while (data->env && data->env[i] && \
			ft_strncmp(data->env[i], *str, len) == FALSE)
		i++;
	if (data->env && data->env[i])
	{
		while (data->env[i][j])
		{
			write(fd, &data->env[i][j], 1);
			j++;
		}
	}
	free(*str);
	*str = NULL;
	return (len);
}

static int	ft_not_expandable(int fd, char *str)
{
	if (str && str[0] && str[1] == '$')
	{
		write (fd, "$$", 2);
		return (2);
	}
	write(fd, "$", 1);
	return (1);
}

int	ft_expand_heredoc(t_data *data, int fd, char *str)
{
	int		i;
	int		len;
	char	*new_str;

	i = 1;
	len = ft_count_var_len(str);
	if (len < 2)
		return (ft_not_expandable(fd, str));
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_check_malloc(data, new_str);
	while (str[i] && i < len)
	{
		new_str[i - 1] = str[i];
		i++;
	}
	new_str[i - 1] = '=';
	new_str[i] = 0;
	ft_write_env_var(data, fd, &new_str, len);
	return (len);
}

void	ft_redirect_heredoc(t_data *data, t_elem *elem)
{
	int		i;
	t_token	*token;

	i = 0;
	while (elem)
	{
		token = elem->first_token;
		while (token)
		{
			if (ft_strncmp(token->new_str, "<<", -1) == TRUE)
			{
				if (ft_modif_input_heredoc(data, token, i) == FALSE)
					return ;
				i++;
			}
			token = token->next;
		}
		elem = elem->next;
	}
}
