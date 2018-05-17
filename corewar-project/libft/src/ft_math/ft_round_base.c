/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 00:21:48 by rnugroho          #+#    #+#             */
/*   Updated: 2018/02/22 15:51:04 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long int
	ft_round_base(double x, double f, int b)
{
	double		half;
	long int	r;

	r = (long int)(f * 10 + 0.5);
	half = ((double)b) / 2;
	if (r < half)
		return (x);
	else
	{
		x = x + 1;
		while (((long int)x) % (b / 10) != 0)
			x = x + 1;
		return (x);
	}
}
