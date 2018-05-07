/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:39:06 by rnugroho          #+#    #+#             */
/*   Updated: 2017/11/14 16:39:06 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int tens;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n <= -2147483648)
		{
			ft_putchar_fd('2', fd);
			n = -147483648;
		}
		n = n * -1;
	}
	tens = 1;
	while (tens <= n / 10)
		tens = tens * 10;
	while (tens > 0)
	{
		ft_putchar_fd(n / tens + '0', fd);
		n = n % tens;
		tens = tens / 10;
	}
}
