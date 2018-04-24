/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 03:15:30 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/10 03:15:35 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		fill_itoa(char *str, unsigned int n, int size, int base)
{
	str[size] = '\0';
	while (size-- > 0)
	{
		if ((int)n < -2147483647 && base == 10)
		{
			str[size] = '8';
			n = 2147483647;
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

char			*ft_itoa_base(int n, int base)
{
	int		size;
	int		is_neg;
	char	*str;

	is_neg = 0;
	if (base == 10)
		size = (ft_intlen(n));
	else
		size = (ft_intlen_base(n, base));
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
	fill_itoa(str, n, size, base);
	if (is_neg == -1)
		str[0] = '-';
	return (str);
}
