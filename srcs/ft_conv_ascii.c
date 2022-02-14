/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_ascii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:50:58 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 10:51:00 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	ft_atouc(char *str)
{
	int					i;
	int					flag;
	unsigned char		nb;

	i = 0;
	flag = 0;
	nb = 0;
	if (str && str[i] == '-')
	{
		flag = 1;
		i += 1;
	}
	while (str && str[i])
	{
		nb = (nb * 10) + str[i] - 48;
		i++;
	}
	if (flag == 1)
		nb *= -1;
	return (nb);
}

int	ft_atol(char *str)
{
	int					i;
	int					flag;
	unsigned long		nb;
	unsigned long		max;

	i = 0;
	flag = 0;
	nb = 0;
	max = 9223372036854775808U;
	if (str && str[i] == '-')
	{
		flag = 1;
		i += 1;
	}
	while (str && str[i])
	{
		nb = (nb * 10) + str[i] - 48;
		i++;
	}
	if (nb > 9223372036854775807 && flag == 0)
		return (FALSE);
	if (nb > max && flag == 1)
		return (FALSE);
	return (TRUE);
}
