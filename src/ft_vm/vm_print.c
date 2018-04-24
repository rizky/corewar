/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:41:04 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/25 01:19:25 by rnugroho         ###   ########.fr       */
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

void	vm_print_verbose(t_vm vm, int i)
{
	ft_printfln("magic: %x", vm.champ[i].header.magic);
	ft_printfln("name: %s", vm.champ[i].header.prog_name);
	ft_printfln("size: %d", vm.champ[i].header.prog_size);
	ft_printfln("comment: %s", vm.champ[i].header.comment);
	ft_printfln("operations:");
	ft_printfln("%*m", vm.champ[i].header.prog_size, vm.champ[i].op);
}

void	vm_print_memory(unsigned char memory[MEM_SIZE])
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i > 0 && i % 64 == 0)
			ft_printf("\n");
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02x ", memory[i]);
		i++;
	}
	ft_printf("\n");
}

int		vm_get_cursor_color(t_vm vm, int index)
{
	int		j;
	int		k;

	j = 0;
	while (j < vm.champ_size)
	{
		k = 0;
		while (k < (int)(vm.champ[j].processes->size))
		{
			if (((t_process*)vm.champ[j].processes->data)[k].offset +
				((t_process*)vm.champ[j].processes->data)[k].pc == index)
				return (j + 1);
			k++;
		}
		j++;
	}
	return (0);
}

void	vm_print_memory_cursor(unsigned char memory[MEM_SIZE], t_vm vm)
{
	int		i;
	int		color;

	i = 0;
	ft_printf("\033[H\033[J");
	ft_printfln("Cycles %d", g_cycles);
	while (i < MEM_SIZE)
	{
		if (i > 0 && i % 64 == 0)
			ft_printf("\n");
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		color = vm_get_cursor_color(vm, i);
		if (color)
			ft_printf("%*W%02x %w", color, memory[i]);
		else
			ft_printf("%*w%02x %w", g_memory_mark[i], memory[i]);
		i++;
	}
	ft_printf("\n");
	system("sleep 0.0001");
}
