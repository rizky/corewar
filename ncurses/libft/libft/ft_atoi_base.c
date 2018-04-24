/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 05:03:01 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/14 05:03:03 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_calc_base(const char *s, int base, int i)
{
	int result;

	result = 0;
	if (base <= 10)
	{
		while (s[i] != '\0' && (s[i] >= '0' && s[i] <= '9'))
		{
			result = result * base + s[i] - '0';
			i++;
		}
	}
	else
	{
		while (s[i] != '\0' && ((s[i] >= '0' && s[i] <= '9')
			|| (s[i] >= 'A' && s[i] <= ('A' + base - 10))
			|| (s[i] >= 'a' && s[i] <= ('a' + base - 10))))
		{
			if (s[i] >= 'A' || s[i] >= 'a')
				result = result * base + (s[i] - 'A' + 10);
			else
				result = result * base + s[i] - '0';
			i++;
		}
	}
	return (result);
}

int			ft_atoi_base(const char *str, int base)
{
	int i;
	int result;
	int is_negative;

	i = 0;
	result = 0;
	is_negative = 1;
	if (base <= 1 || base > 16)
		return (0);
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' && base == 10)
			is_negative = -1;
		i++;
	}
	result = ft_calc_base(str, base, i);
	return (is_negative * result);
}
