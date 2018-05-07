/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:38:49 by rnugroho          #+#    #+#             */
/*   Updated: 2017/11/14 16:38:53 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int tens;

	if (n < 0)
	{
		ft_putchar('-');
		if (n <= -2147483648)
		{
			ft_putchar('2');
			n = -147483648;
		}
		n = n * -1;
	}
	tens = 1;
	while (tens <= n / 10)
		tens = tens * 10;
	while (tens > 0)
	{
		ft_putchar(n / tens + '0');
		n = n % tens;
		tens = tens / 10;
	}
}
