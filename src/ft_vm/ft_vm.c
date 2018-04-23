/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:38:33 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/23 16:11:39 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	*vm_memmark(void *dst, int i, size_t n)
{
	unsigned char	*dst_p;

	dst_p = (unsigned char*)dst;
	while (n-- > 0)
		*dst_p++ = i;
	return (dst);
}

void
	vm_load_champs(t_vm *vm, unsigned char memory[MEM_SIZE])
{
	int			i;
	t_process	p;

	i = 0;
	vm->cycles_to_die = 10;
	ft_bzero(&p, sizeof(t_process));
	ft_printfln("Introducing contestants...");
	while (i < vm->champ_size)
	{
		ft_printfln("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !", i + 1,
		vm->champ[i].header.prog_size, vm->champ[i].header.prog_name,
		vm->champ[i].header.comment);
		ft_memcpy(&memory[i * MEM_SIZE / vm->champ_size], vm->champ[i].op,
				vm->champ[i].header.prog_size);
		vm_memmark(&g_memory_mark[i * MEM_SIZE / vm->champ_size], i + 1,
				vm->champ[i].header.prog_size);
		p.offset = i * MEM_SIZE / vm->champ_size;
		fta_append(vm->champ[i].processes, &p, 1);
		i++;
	}
}

int
	main(int ac, char **av)
{
	t_vm			vm;
	int				i;
	static	int		opt[OPT_NUM] = {0, 0};

	ft_bzero(&g_memory, MEM_SIZE);
	ft_bzero(&g_memory_mark, MEM_SIZE);
	if ((i = vm_getoptions(av, opt)) == -1)
		return (vm_print_usage(av, -1));
	ft_bzero(&vm, sizeof(t_vm));
	while (i < ac)
	{
		if (vm.champ_size > 3)
			return (vm_print_usage(av, -1));
		if ((i = vm_read_binary(i, av, &vm)) == -1)
			return (-1);
		i++;
	}
	i = -1;
	if (opt[OPT_V])
		while (++i < vm.champ_size)
			vm_print_verbose(vm, i);
	vm_load_champs(&vm, g_memory);
	while (vm.cycles < vm.cycles_to_die)
	{
		system("sleep 1");
		system("clear");
		vm_executor(&vm);
		vm_print_memory_cursor(g_memory, vm);
		vm.cycles++;
	}
	return (0);
}
