/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:17:40 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 13:59:32 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect_input(t_elem *elem, t_token *token)
{
	int	fd;

	fd = open(token->next->new_str, O_RDONLY);
	ft_check_open(fd, token->next->new_str, token->next->str);
	if (fd == -1)
		elem->redirect = FALSE;
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	ft_redirect_output(t_elem *elem, t_token *token, int flag)
{
	int	fd;

	fd = -1;
	if (flag == 1)
		fd = open(token->next->new_str, O_CREAT | O_WRONLY | O_TRUNC, 00664);
	else if (flag == 2)
		fd = open(token->next->new_str, O_CREAT | O_WRONLY | O_APPEND, 00664);
	ft_check_open(fd, token->next->new_str, token->next->str);
	if (fd == -1)
		elem->redirect = FALSE;
	else
	{
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
}
