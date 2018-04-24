/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 06:04:05 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/20 06:04:07 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int		ft_llong_len(long long int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static void		fill(char *str, long long int n, int is_neg, int size)
{
	str[size] = '\0';
	while (size-- > 0)
	{
		if (size == 0 && is_neg == -1)
			str[size] = '-';
		else if (n == LLONG_MIN)
		{
			str[size] = '8';
			n = LLONG_MAX;
		}
		else
			str[size] = ((n % 10) + '0');
		n = n / 10;
	}
}

char			*ft_lltoa(long long int n)
{
	int		size;
	int		is_negative;
	char	*str;

	is_negative = 0;
	size = ft_llong_len(n);
	if (n < 0)
	{
		is_negative = -1;
		n = n * is_negative;
	}
	if ((str = ft_strnew(size)) == NULL)
		return (NULL);
	fill(str, n, is_negative, size);
	return (str);
}
