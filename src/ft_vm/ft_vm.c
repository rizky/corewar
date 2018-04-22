/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:38:33 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/22 21:05:39 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_load_champs(t_vm vm, unsigned char memory[MEM_SIZE])
{
	int		i;

	i = 0;
	while (i < vm.champ_size)
	{
		ft_memcpy(&memory[i * MEM_SIZE / vm.champ_size], vm.champ[i].op,
				vm.champ[i].header.prog_size);
		i++;
	}
}

int
	main(int ac, char **av)
{
	t_vm			vm;
	int				i;
	static	int		opt[OPT_NUM] = {0, 1};
	unsigned char	memory[MEM_SIZE];

	ft_bzero(&memory, MEM_SIZE);
	if ((i = vm_getoptions(av, opt)) == -1)
		return (vm_print_usage(av, -1));
	ft_bzero(&vm, sizeof(t_vm));
	if (opt[OPT_N] > 4)
		return (vm_error(CHAMP_MAX, -1));
	while (opt[OPT_N] > 0 || i < ac)
	{
		if (i >= ac || opt[OPT_N] == 0)
			return (vm_print_usage(av, -1));
		vm_read_binary(i, av, &vm);
		i++;
		opt[OPT_N]--;
	}
	i = -1;
	while (++i < vm.champ_size)
		vm_print_verbose(vm, i);
	vm_load_champs(vm, memory);
	vm_print_memory(memory);
	return (0);
}
