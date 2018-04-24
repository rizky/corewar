/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_helper_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:58:02 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/24 17:21:17 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int		vm_print_usage(char **av, int status)
{
		ft_dprintf(2, "usage: %s [-dump nbr_cycles] ", av[0]);
		ft_dprintf(2, "[-v N ...] [-n number] champion1.cor ...\n");
		ft_dprintf(2, "    -v N      : Verbosity levels");
		ft_dprintf(2, ", can be added together to enable several\n");
		ft_dprintf(2, "                - 0 : Show only essentials\n");
		ft_dprintf(2, "                - 1 : Show lives\n");
		ft_dprintf(2, "                - 2 : Show cycles\n");
		ft_dprintf(2, "                - 4 : Show operations ");
		ft_dprintf(2, "(Params are NOT literal ...\n");
		ft_dprintf(2, "                - 8 : Show deaths\n");
		ft_dprintf(2, "                - 16 : Show PC movements ");
		ft_dprintf(2, "(Except for jumps)\n");
		return (status);
}

int		ft_isnumber(char *str)
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

int		ft_abs(int i)
{
	if (i < 0)
		return (i *= -1);
	return (i);
}
