/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 12:15:39 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/25 14:45:21 by rnugroho         ###   ########.fr       */
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
	vm_checker(t_vm *vm)
{
	int live_nbr;

	live_nbr = vm_checker_livenbr(*vm);
	if (g_cycles_to == g_cycles_to_die)
	{
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
