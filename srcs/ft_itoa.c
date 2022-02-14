/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echuong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:01:36 by echuong           #+#    #+#             */
/*   Updated: 2022/02/07 11:01:43 by echuong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_count_digits(int n)
{
	int	i;

	i = 1;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static	char	*ft_copy(char *str, int n, int i)
{
	unsigned int	unb;

	i = i - 1;
	if (n < 0)
		unb = n * -1;
	else
		unb = n;
	while (unb > 9)
	{
		str[i] = (unb % 10) + 48;
		unb = unb / 10;
		i--;
	}
	str[i] = unb + 48;
	return (str);
}

char	*ft_itoa(t_data *data, int n)
{
	int		i;
	char	*str;

	i = ft_count_digits(n);
	if (n < 0)
		i = i + 1;
	str = malloc(sizeof(char) * (i + 1));
	ft_check_malloc(data, str);
	if (n < 0)
		str[0] = '-';
	str[i] = '\0';
	str = ft_copy(str, n, i);
	return (str);
}
