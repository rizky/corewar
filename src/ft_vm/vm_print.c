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
