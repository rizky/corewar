/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:41:04 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/22 20:25:25 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int
	vm_print_usage(char **av, int status)
{
	ft_dprintf(2, "usage: %s [-dump nbr_cycles] [-n number] ", av[0]);
	ft_dprintf(2, "champion1.cor ...\n");
	return (status);
}

void
	vm_print_verbose(t_vm vm, int i)
{
	ft_printfln("magic: %d", vm.champ[i].header.magic);
	ft_printfln("name: %s", vm.champ[i].header.prog_name);
	ft_printfln("size: %d", vm.champ[i].header.prog_size);
	ft_printfln("comment: %s", vm.champ[i].header.comment);
	ft_printfln("%*m", vm.champ[i].header.prog_size, vm.champ[i].op);
}
