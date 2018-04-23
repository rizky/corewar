/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:41:04 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/23 15:41:55 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_print(t_vm vm)
{
	int i;

	i = -1;
	ft_printf("dump: %d cycles: %d\n", vm.dump, vm.cycles);
	ft_printf("is verbose: %d verbosity level: %d\n", vm.verbose, vm.verbosity_lvl);
	while (++i < MAX_PLAYERS)
		ft_printf("player %d: %s\n", i + 1, vm.players[i]);
	ft_printfln("This is Corewar!");
}
