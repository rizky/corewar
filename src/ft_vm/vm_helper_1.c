/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_helper_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:58:02 by fpetras           #+#    #+#             */
/*   Updated: 2018/05/06 07:45:57 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int		vm_valid_arg(char *arg, t_vm *vm)
{
	if (!ft_strcmp(arg, "-dump") || !ft_strcmp(arg, "-dumpc") ||
		!ft_strcmp(arg, "-v") || !ft_strcmp(arg, "-n"))
		return (vm->opt_num = 1);
	else if ((!ft_strncmp(arg, "-v", 2) || !ft_strncmp(arg, "-n", 2)) &&
		ft_isnumber(&arg[2]))
		return ((vm->opt_num = 0) + 1);
	else if (ft_isnumber(arg) && vm->opt_num)
		return ((vm->opt_num = 0) + 1);
	else if (!ft_strcmp(&arg[ft_strlen(arg) - 4], ".cor") ||
		!ft_strcmp(arg, "-g") || !ft_strcmp(arg, "-G") ||
		!ft_strcmp(arg, "-u"))
		return ((vm->opt_num = 0) + 1);
	return (0);
}

int		vm_valid_verbosity_lvl(int v)
{
	if (v == 2 || v == 4 || v == 8 || v == 16)
		return (1);
	else if (v == 6 || v == 10 || v == 12 || v == 14)
		return (1);
	else if (v == 18 || v == 20 || v == 22 || v == 24)
		return (1);
	else if (v == 26 || v == 28 || v == 30)
		return (1);
	else
		return (0);
}

void	vm_set_v_lvl(int v, t_vm *vm)
{
	if (v == 2 || v == 6 || v == 10 || v == 14 ||
		v == 18 || v == 22 || v == 26 || v == 30)
		vm->option_v[V_LVL_2] = 1;
	if (v == 4 || v == 6 || v == 12 || v == 14 ||
		v == 20 || v == 22 || v == 28 || v == 30)
		vm->option_v[V_LVL_4] = 1;
	if (v == 8 || v == 10 || v == 12 || v == 14 ||
		v == 24 || v == 26 || v == 28 || v == 30)
		vm->option_v[V_LVL_8] = 1;
	if (v == 16 || v == 18 || v == 20 || v == 22 ||
		v == 24 || v == 26 || v == 28 || v == 30)
		vm->option_v[V_LVL_16] = 1;
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
	if (ft_atoll(str) < -2147483648 || ft_atoll(str) > 2147483647)
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
