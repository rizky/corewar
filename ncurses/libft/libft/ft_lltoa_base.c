/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 06:10:28 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/20 06:10:30 by jyeo             ###   ########.fr       */
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

static int		ft_llong_len_base(unsigned long long int n, int base)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / base;
		size++;
	}
	return (size);
}

static void		fill(char *str, unsigned long long int n, int size, int base)
{
	str[size] = '\0';
	while (size-- > 0)
	{
		if ((long long int)n == LLONG_MIN && base == 10)
		{
			str[size] = '8';
			n = LLONG_MAX;
		}
		else
		{
			if (n % base > 9)
				str[size] = (((n % base) - 10) + 'a');
			else
				str[size] = ((n % base) + '0');
		}
		n = n / base;
	}
}

char			*ft_lltoa_base(long long int n, int base)
{
	int		size;
	int		is_neg;
	char	*str;

	is_neg = 0;
	if (base == 10)
		size = (ft_llong_len(n));
	else
		size = (ft_llong_len_base(n, base));
	if (n < 0)
	{
		if (base == 10)
		{
			is_neg = -1;
			n *= -1;
		}
	}
	if ((str = ft_strnew(size)) == NULL)
		return (NULL);
	fill(str, n, size, base);
	if (is_neg == -1)
		str[0] = '-';
	return (str);
}
