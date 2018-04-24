/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:41:04 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/24 18:52:13 by fpetras          ###   ########.fr       */
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
