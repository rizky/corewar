/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 03:48:08 by jyeo              #+#    #+#             */
/*   Updated: 2018/02/04 03:48:10 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_check_int(int i, int len, int is_neg, char *str)
{
	long long	tmp;

	tmp = 0;
	while (i < len)
	{
		if (!(ft_isdigit(str[i])))
			return (-1);
		tmp = tmp * 10 + (str[i] - '0');
		if ((!is_neg && tmp > 2147483647) || (is_neg && -tmp < -2147483648))
			return (-1);
		i++;
	}
	return (0);
}

int				ft_valid_int(char *str)
{
	int			i;
	int			is_neg;

	i = 0;
	is_neg = 0;
	if (str[i] == '-')
	{
		if (ft_isdigit(str[i + 1]))
			is_neg = 1;
		else
			return (-1);
		i++;
	}
	if ((ft_check_int(i, (int)ft_strlen(str), is_neg, str)) == -1)
		return (-1);
	return (0);
}
