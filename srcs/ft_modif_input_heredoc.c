/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modif_input_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:01:55 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:39:13 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect_input_heredoc(t_data *data, t_token *token, char *path)
{
	free(token->new_str);
	token->new_str = ft_strdup_t(data, "<", -1);
	if (token->next)
	{
		if (token->next->new_str)
			free(token->next->new_str);
		token->next->new_str = ft_strdup_t(data, path, -1);
	}
}

int	ft_modif_input_heredoc(t_data *data, t_token *token, int i)
{
	char	*path;
	char	*nbr;
	int		fd;

	g_global = 0;
	nbr = ft_itoa(data, i);
	path = ft_strjoin(data, "/tmp/heredoc", nbr, 1);
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 00664);
	ft_check_open(fd, path, path);
	if (ft_get_line(data, &token->next->new_str, fd) == FALSE)
	{
		close(fd);
		free(nbr);
		free(path);
		dup2(data->cpy_stdin, STDIN_FILENO);
		return (FALSE);
	}
	ft_redirect_input_heredoc(data, token, path);
	close(fd);
	free(nbr);
	free(path);
	return (TRUE);
}
