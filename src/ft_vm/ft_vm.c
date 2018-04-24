/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:38:33 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/24 19:20:21 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

static int	vm_populate_players(int i, char **av, t_vm *vm)
{
	int j;

	j = 0;
	while (vm->players[j])
		j++;
	if (j <= 4)
		vm->players[j] = av[i];
	else
		return (-1);
	return (0);
}

static int	vm_get_champions(char **av, t_vm *vm)
{
	int i;
	int j;
	int equ;
	int num;

	i = 0;
	num = 0;
	while (av[++i])
	{
		j = -1;
		equ = 0;
		if (ft_strequ(&av[i][ft_strlen(av[i]) - 4], ".cor"))
		{
			while (++j < 4)
				if (ft_strequ(av[i], vm->players[j]) && av[i] == vm->players[j])
					equ = 1;
			if (!equ && vm_populate_players(i, av, vm) == -1)
				return (MAX_PLAYERS + 1);
			num++;
		}
	}
	ft_printf("%d\n", num);
	return (num);
}

int			main(int ac, char **av)
{
	t_vm vm;

	ft_bzero(&vm, sizeof(t_vm));
	if (ac < 2 || vm_options(av, &vm) == -1)
		return (vm_print_usage(av, -1));
	else if (vm_get_champions(av, &vm) > MAX_PLAYERS)
	{
		ft_dprintf(2, "Too many champions\n");
		return (-1);
	}
	vm_print(vm);
	return (0);
}
