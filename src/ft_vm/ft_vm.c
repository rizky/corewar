/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:38:33 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/23 15:42:32 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

static int	vm_get_champions(char **av, t_vm *vm)
{
	int i;
	int j;
	int equ;
	int num;

	i = 0;
	equ = 0;
	num = 0;
	while (av[++i])
	{
		j = -1;
		equ = 0;
		if (ft_strequ(&av[i][ft_strlen(av[i]) - 4], ".cor"))
		{
			while (++j < 4)
				if (ft_strequ(av[i], vm->players[j]))
					equ = 1;
			j = 0;
			if (!equ)
			{
				while (vm->players[j])
					j++;
				if (j <= 4)
					vm->players[j] = av[i];
				else
					return (MAX_PLAYERS + 1);
			}
			num++;
		}
	}
	return (num);
}

int			main(int ac, char **av)
{
	t_vm vm;

	ft_bzero(&vm, sizeof(t_vm));
	if (ac < 2 || vm_options(av, &vm) == -1)
	{
		ft_dprintf(2, "usage: %s [-dump nbr_cycles] [-n number] ", av[0]);
		ft_dprintf(2, "champion1.cor ...\n");
		return (-1);
	}
	else if (vm_get_champions(av, &vm) > MAX_PLAYERS)
	{
		ft_dprintf(2, "Too many champions\n");
		return (-1);
	}
	vm_print(vm);
	return (0);
}
