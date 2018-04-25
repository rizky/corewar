/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_helper_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:58:02 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/25 07:59:18 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int		vm_valid_arg(char *arg, t_vm *vm)
{
	if (!ft_strcmp(arg, "-dump") || !ft_strcmp(arg, "-v") ||
		!ft_strcmp(arg, "-n"))
	{
		if (!ft_strcmp(arg, "-dump"))
			return (vm->valid_arg[0] = 1);
		else
			return (vm->valid_arg[1] = 1);
	}
	else if ((!ft_strncmp(arg, "-v", 2) || !ft_strncmp(arg, "-n", 2)) &&
		ft_isnumber(&arg[2]))
	{
		return (vm->valid_arg[1] = 1);
	}
	else if (ft_isnumber(arg) && (vm->valid_arg[0] || vm->valid_arg[1]))
	{
		vm->valid_arg[0] = 0;
		return (1);
	}
	else if (!ft_strcmp(&arg[ft_strlen(arg) - 4], ".cor"))
	{
		vm->valid_arg[0] = 0;
		vm->valid_arg[1] = 0;
		return (1);
	}
	return (0);
}

int		vm_valid_verbosity_lvl(int v)
{
	return (v == 0 || v == 1 || v == 2 || v == 4 || v == 8 || v == 16);
}

int		vm_lvl_to_index(int lvl)
{
	if (lvl == 0 || lvl == 1 || lvl == 2)
		return (lvl);
	else if (lvl == 4)
		return (V_LVL_4);
	else if (lvl == 8)
		return (V_LVL_8);
	else if (lvl == 16)
		return (V_LVL_16);
	else
		return (0);
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
