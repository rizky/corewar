/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:11:44 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/24 21:16:09 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

/*
** To-do: Protect ft_atoi
*/

static int	vm_valid_verbosity_lvl(int v)
{
	return (v == 0 || v == 1 || v == 2 || v == 4 || v == 8 || v == 16);
}

static int	vm_lvl_to_index(int lvl)
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

static int	vm_option_v(int i, char **av, t_vm *vm)
{
	int lvl;

	if (!ft_strcmp(av[i], "-v"))
	{
		if (!ft_isnumber(av[i + 1]))
			return (-1);
		while (av[++i] && ft_isnumber(av[i]))
		{
			lvl = ft_atoi(av[i]);
			if (!vm_valid_verbosity_lvl(lvl))
				return (-1);
			vm->v_lvl[vm_lvl_to_index(lvl)] =
			(vm_valid_verbosity_lvl(lvl)) ? 1 : vm->v_lvl[lvl];
		}
	}
	else if (!ft_strncmp(av[i], "-v", 2))
	{
		if (!ft_isnumber(&av[i][2]))
			return (-1);
		lvl = ft_atoi(&av[i][2]);
		if (!vm_valid_verbosity_lvl(lvl))
			return (-1);
		vm->v_lvl[vm_lvl_to_index(lvl)] =
		(vm_valid_verbosity_lvl(lvl)) ? 1 : vm->v_lvl[lvl];
		while (av[++i] && ft_isnumber(av[i]))
		{
			lvl = ft_atoi(av[i]);
			if (!vm_valid_verbosity_lvl(lvl))
				return (-1);
			vm->v_lvl[vm_lvl_to_index(lvl)] =
			(vm_valid_verbosity_lvl(lvl)) ? 1 : vm->v_lvl[lvl];
		}
	}
	return (0);
}

static int	vm_option_n(int i, char **av, t_vm *vm)
{
	int num;

	num = 1;
	if (!ft_strcmp(av[i], "-n"))
	{
		num = ft_abs(ft_atoi(av[i + 1]));
		if (num < 1 || num > MAX_PLAYERS)
			return (-1);
		if (!av[i + 2] ||
			!ft_strequ(&av[i + 2][ft_strlen(av[i + 2]) - 4], ".cor"))
			return (-1);
		vm->players[num - 1] = av[i + 2];
	}
	else if (!ft_strncmp(av[i], "-n", 2))
	{
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

int			vm_options(char **av, t_vm *vm)
{
	int i;

	i = 0;
	while (av[++i])
	{
		if (!ft_strcmp(av[i], "-dump"))
		{
			if ((vm->dump = ft_atoi(av[i + 1])) <= 0)
				return (-1);
		}
		else if (vm_option_n(i, av, vm) == -1)
			return (-1);
		else if (vm_option_v(i, av, vm) == -1)
			return (-1);
//		if (ft_strncmp(av[i], "-n", 2) && ft_strcmp(av[i], "-dump") &&
//			ft_strcmp(&av[i][ft_strlen(av[i]) - 4], ".cor") &&
//			ft_atoi(av[i]) <= 0)
//			return (-1);
	}
	return (0);
}

void	vm_print(t_vm vm)
{
	int i;
	int j;

	ft_printf("dump: %d cycles: %d\n", vm.dump, vm.cycles);
	i = -1;
	j = 0;
	while (++i < 6)
	{
		j = (i == 3) ? 4 : j;
		j = (i == 4) ? 8 : j;
		j = (i == 5) ? 16 : j;
		ft_printf("verbosity lvl %d: %d\n", j, vm.v_lvl[i]);
		j++;
	}
	i = -1;
	while (++i < MAX_PLAYERS)
		ft_printf("player %d: %s\n", i + 1, vm.players[i]);
	ft_printfln("This is Corewar!");
}
