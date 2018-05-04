/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:41:04 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/04 16:19:04 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int
	vm_print_usage(char **av, int status)
{
	ft_dprintf(2, "usage: %s [-dump nbr_cycles] ", av[0]);
	ft_dprintf(2, "[-v N...] [-n number] champion1.cor ...\n");
	ft_dprintf(2, "    -v N      : Verbosity levels");
	ft_dprintf(2, ", can be added together to enable several\n");
	ft_dprintf(2, "                - 0 : Show only essentials\n");
	ft_dprintf(2, "                - 1 : Show visualization\n");
	ft_dprintf(2, "                - 2 : Show cycles\n");
	ft_dprintf(2, "                - 4 : Show operations ");
	ft_dprintf(2, "(Params are NOT literal ...)\n");
	ft_dprintf(2, "                - 8 : Show deaths\n");
	ft_dprintf(2, "                - 16 : Show PC movements ");
	ft_dprintf(2, "(Except for jumps)\n");
	return (status);
}

void
	vm_print_memory(void)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i > 0 && i % 64 == 0)
			ft_printf("\n");
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02x ", g_memory[i]);
		i++;
	}
	ft_printf("\n");
}

static int
	vm_get_cursor_color(t_vm vm, int index)
{
	int		k;

	k = 0;
	while (k < (int)(vm.processes.size))
	{
		if (((t_process*)vm.processes.data)[k].offset +
			((t_process*)vm.processes.data)[k].pc == index)
			return (((t_process*)vm.processes.data)[k].champ + 1);
		k++;
	}
	return (0);
}

void
	vm_print_memory_cursor(t_vm vm)
{
	int		i;
	int		color;

	if (g_cycles % 20 != 0)
		return ;
	i = 0;
	ft_printf("%0.0v%150Q%0.0vCycles:%4d\tCTD:%4d/%4d(-%d)",
		' ', g_cycles, g_cycles_to, g_cycles_to_die, CYCLE_DELTA);
	ft_printfln("\tLives:%4d\tProcesses:%4d\tMax Check:%2d/%2d",
		vm_checker_livenbr(vm), vm.processes.size,
		g_max_check, MAX_CHECKS);
	while (i < MEM_SIZE)
	{
		if (i > 0 && i % 64 == 0)
			ft_printf("\n");
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		color = vm_get_cursor_color(vm, i);
		if (color)
			ft_printf("%*W%02x %w", color, g_memory[i]);
		else
			ft_printf("%*w%02x %w", g_memory_mark[i], g_memory[i]);
		i++;
	}
	ft_printf("\n");
}

void
	vm_print_memory_color(t_vm vm)
{
	int		i;
	int		color;

	i = 0;
	ft_printf("%0.0v%150Q%0.0vCycles:%4d\tCTD:%4d/%4d(-%d)",
		' ', g_cycles, g_cycles_to, g_cycles_to_die, CYCLE_DELTA);
	ft_printfln("\tLives:%4d\tProcesses:%4d\tMax Check:%2d/%2d",
		vm_checker_livenbr(vm), vm.processes.size,
		g_max_check, MAX_CHECKS);
	while (i < MEM_SIZE)
	{
		if (i > 0 && i % 64 == 0)
			ft_printf("\n");
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		color = vm_get_cursor_color(vm, i);
		if (color)
			ft_printf("%*W%02x %w", color, g_memory[i]);
		else
			ft_printf("%*w%02x %w", g_memory_mark[i], g_memory[i]);
		i++;
	}
	ft_printf("\n");
}
