/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:38:33 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/22 20:53:39 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int
	main(int ac, char **av)
{
	t_vm			vm;
	int				i;
	static	int		opt[OPT_NUM] = {0, 1};
	char			memory[MEM_SIZE];

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
	vm_print_memory(memory);
	return (0);
}
