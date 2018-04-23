/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_helper_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:58:02 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/20 16:44:43 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int		vm_isnumber(char *str)
{
	int i;
	int sign;
	int digit;

	i = -1;
	sign = 0;
	digit = 0;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			sign++;
			if (sign > 1 || digit > 0)
				return (0);
		}
		else if (ft_isdigit(str[i]))
			digit++;
		else
			return (0);
	}
	return (digit > 0);
}
