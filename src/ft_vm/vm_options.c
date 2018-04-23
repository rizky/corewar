/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:11:44 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/23 23:20:29 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

/*
** To-do: Protect ft_atoi
*/

static int	vm_options_2(int i, char **av, t_vm *vm)
{
	int num;

	num = 1;
	if (!ft_strcmp(av[i], "-n"))
	{
		num = ft_atoi(av[i + 1]);
		if (num < 1 || num > MAX_PLAYERS)
			return (-1);
		if (!av[i + 2] ||
			!ft_strequ(&av[i + 2][ft_strlen(av[i + 2]) - 4], ".cor"))
			return (-1);
		vm->players[num - 1] = av[i + 2];
	}
	else if (!ft_strncmp(av[i], "-n", 2))
	{
		num = ft_atoi(&av[i][2]);
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
			vm->dump = 1;
			if ((vm->cycles = ft_atoi(av[i + 1])) <= 0)
				return (-1);
		}
		else if (vm_options_2(i, av, vm) == -1)
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

	i = -1;
	ft_printf("dump: %d cycles: %d\n", vm.dump, vm.cycles);
	while (++i < MAX_PLAYERS)
		ft_printf("player %d: %s\n", i + 1, vm.players[i]);
}
