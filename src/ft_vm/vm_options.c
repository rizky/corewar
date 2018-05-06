/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:11:44 by fpetras           #+#    #+#             */
/*   Updated: 2018/05/06 08:39:59 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

static int	vm_opt_n_2(int i, char **av, t_vm *vm)
{
	int num;

	if (!ft_strncmp(av[i], "-n", 2))
	{
		if (!ft_isnumber(&av[i][2]))
			return (-1);
		num = ft_abs(ft_atoi(&av[i][2]));
		if (num < 1 || num > MAX_PLAYERS)
			return (-1);
		if (!av[i + 1] ||
			!ft_strequ(&av[i + 1][ft_strlen(av[i + 1]) - 4], ".cor"))
			return (-1);
		vm->players[num - 1] = av[i + 1];
	}
	return (0);
}

static int	vm_opt_n(int i, char **av, t_vm *vm)
{
	int num;

	num = 1;
	if (!ft_strcmp(av[i], "-n"))
	{
		if (!ft_isnumber(av[i + 1]))
			return (-1);
		num = ft_abs(ft_atoi(av[i + 1]));
		if (num < 1 || num > MAX_PLAYERS)
			return (-1);
		if (!av[i + 2] ||
			!ft_strequ(&av[i + 2][ft_strlen(av[i + 2]) - 4], ".cor"))
			return (-1);
		vm->players[num - 1] = av[i + 2];
	}
	else if (vm_opt_n_2(i, av, vm) == -1)
		return (-1);
	return (0);
}

static int	vm_opt_v_2(int i, char **av, t_vm *vm)
{
	int lvl;

	if (!ft_strncmp(av[i], "-v", 2))
	{
		if (!ft_isnumber(&av[i][2]))
			return (-1);
		lvl = ft_atoi(&av[i][2]);
		if (!vm_valid_verbosity_lvl(lvl))
			return (-1);
		vm_set_v_lvl(lvl, vm);
	}
	return (0);
}

static int	vm_opt_v(int i, char **av, t_vm *vm)
{
	int lvl;

	if (!ft_strcmp(av[i], "-v"))
	{
		if (!ft_isnumber(av[i + 1]))
			return (-1);
		lvl = ft_atoi(av[i + 1]);
		if (!vm_valid_verbosity_lvl(lvl))
			return (-1);
		vm_set_v_lvl(lvl, vm);
	}
	else if (vm_opt_v_2(i, av, vm) == -1)
		return (-1);
	return (0);
}

int			vm_options(char **av, t_vm *vm)
{
	int i;

	i = 0;
	while (av[++i])
	{
		if (!vm_valid_arg(av[i], vm))
			return (-1);
		if (!ft_strcmp(av[i], "-dump") || !ft_strcmp(av[i], "-dumpc"))
		{
			if (!ft_isnumber(av[i + 1]) ||
				((vm->cycles = ft_atoi(av[i + 1])) < 0))
				return (-1);
			vm->dump = (!ft_strcmp(av[i], "-dump")) ? 1 : 2;
		}
		else if ((vm_opt_v(i, av, vm) == -1) || (vm_opt_n(i, av, vm) == -1))
			return (-1);
		else if (!ft_strcmp(av[i], "-u"))
			vm->dump = 3;
		else if (!ft_strcmp(av[i], "-g") && !vm->option_g[VISU_2])
			vm->option_g[VISU_1] = 1;
		else if (!ft_strcmp(av[i], "-G") && !vm->option_g[VISU_1])
			vm->option_g[VISU_2] = 1;
	}
	vm->option_g[VISU_2] ? ft_bzero(vm->option_v, sizeof(vm->option_v)) : 0;
	return (0);
}
