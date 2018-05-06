/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 12:15:39 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/05 18:21:00 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int			vm_checker_livenbr(t_vm vm)
{
	int			j;
	int			live_nbr;
	t_process	*p;

	live_nbr = 0;
	j = -1;
	while (++j < (int)(vm.processes.size))
	{
		p = &(((t_process*)vm.processes.data)[j]);
		live_nbr += p->live_nbr;
	}
	return (live_nbr);
}

static void	vm_reset_livenbr(t_vm *vm)
{
	int			j;
	t_process	*p;

	j = -1;
	g_live_nbr = 0;
	while (++j < (int)(vm->processes.size))
	{
		p = &(((t_process*)vm->processes.data)[j]);
		p->live_nbr = 0;
		vm->champ[p->champ].live_nbr = 0;
	}
}

static int	vm_checker_processalive(t_vm *vm)
{
	int			j;
	int			palive_nbr;
	t_process	*p;

	j = (int)(vm->processes.size) - 1;
	palive_nbr = 0;
	while (j >= 0)
	{
		p = &(((t_process*)vm->processes.data)[j]);
		if (p->live_nbr == 0)
		{
			(vm->option_v[V_LVL_8]) ?
				ft_printfln("Process %d hasn't lived for %d cycles (CTD %d)",
				p->index, g_cycles - p->live_cycle, g_cycles_to_die) : 0;
			fta_popindex(&(vm->processes), j, 1);
			j = (int)(vm->processes.size);
		}
		else
			palive_nbr++;
		j--;
	}
	return (palive_nbr);
}

static void	vm_process_kill(t_vm *vm)
{
	t_process	*p;

	while (vm->processes.size > 0)
	{
		p = &(((t_process*)vm->processes.data)[vm->processes.size - 1]);
		(vm->option_v[V_LVL_8]) ?
			ft_printfln("Process %d hasn't lived for %d cycles (CTD %d)",
			p->index, g_cycles - p->live_cycle, g_cycles_to_die) : 0;
		fta_popindex(&(vm->processes), vm->processes.size - 1, 1);
	}
}

int			vm_checker(t_vm *vm)
{
	if (g_cycles_to_die < 0)
	{
		vm_process_kill(vm);
		if ((g_live_nbr >= NBR_LIVE || ++g_max_check == MAX_CHECKS) &&
			(vm->option_v[V_LVL_2]))
			ft_printfln("Cycle to die is now %d",
				g_cycles_to_die - CYCLE_DELTA);
		return (0);
	}
	if (g_cycles_to == g_cycles_to_die)
	{
		g_cycles_to = 0;
		if (vm_checker_processalive(vm) < 1)
			return (0);
		if (g_live_nbr >= NBR_LIVE || ++g_max_check == MAX_CHECKS)
		{
			g_max_check = 0;
			g_cycles_to_die -= CYCLE_DELTA;
			(vm->option_v[V_LVL_2]) ?
			ft_printfln("Cycle to die is now %d", g_cycles_to_die) : 0;
		}
		vm_reset_livenbr(vm);
	}
	return (1);
}
