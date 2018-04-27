/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 12:15:39 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/27 03:07:29 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int
	vm_checker_livenbr(t_vm vm)
{
	int			i;
	int			j;
	int			live_nbr;
	t_process	*p;

	live_nbr = 0;
	i = -1;
	while (++i < vm.champ_size)
	{
		j = -1;
		while (++j < (int)(vm.champ[i].processes->size))
		{
			p = &(((t_process*)vm.champ[i].processes->data)[j]);
			live_nbr += p->live_nbr;
		}
	}
	return (live_nbr);
}

void
	vm_reset_livenbr(t_vm *vm)
{
	int			i;
	int			j;
	t_process	*p;

	i = -1;
	while (++i < vm->champ_size)
	{
		j = -1;
		while (++j < (int)(vm->champ[i].processes->size))
		{
			p = &(((t_process*)vm->champ[i].processes->data)[j]);
			p->live_nbr = 0;
		}
	}
}

int
	vm_checker_processnbr(t_vm vm)
{
	int			i;
	int			j;
	int			process_nbr;
	t_process	*p;

	process_nbr = 0;
	i = -1;
	while (++i < vm.champ_size)
	{
		j = -1;
		while (++j < (int)(vm.champ[i].processes->size))
		{
			p = &(((t_process*)vm.champ[i].processes->data)[j]);
			process_nbr++;
		}
	}
	return (process_nbr);
}

int
	vm_checker_processalive(t_vm vm, int *winner)
{
	int			i;
	int			j;
	int			palive_nbr;
	int			calive_nbr;
	t_process	*p;

	calive_nbr = 0;
	i = -1;
	while (++i < vm.champ_size)
	{
		j = -1;
		palive_nbr = 0;
		while (++j < (int)(vm.champ[i].processes->size))
		{
			*winner = i;
			p = &(((t_process*)vm.champ[i].processes->data)[j]);
			if (p->live_nbr > 0)
				palive_nbr++;
			else
				fta_popindex(vm.champ[i].processes, j, 1);
		}
		if (palive_nbr > 0)
			calive_nbr++;
	}
	return (calive_nbr);
}

int
	vm_checker(t_vm *vm)
{
	int live_nbr;
	int winner;

	live_nbr = vm_checker_livenbr(*vm);
	if (g_cycles_to == g_cycles_to_die)
	{
		if (vm_checker_processalive(*vm, &winner) <= 1)
		{
			if (vm->v_lvl[V_LVL_4])
				ft_printfln("Contestant %d, \"%s\", has won !",
					winner + 1, vm->champ[winner].header.prog_name);
			return (0);
		}
		g_cycles_to = 0;
		g_max_check++;
		if (live_nbr > NBR_LIVE || g_max_check == MAX_CHECKS)
		{
			g_max_check = g_max_check == MAX_CHECKS ? 0 : g_max_check;
			g_cycles_to_die -= CYCLE_DELTA;
		}
		vm_reset_livenbr(vm);
	}
	if (g_cycles_to_die < 0)
		return (0);
	return (1);
}
