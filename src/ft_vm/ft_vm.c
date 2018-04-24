/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:38:33 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/25 00:43:36 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	*vm_memmark(void *dst, int i, size_t n)
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
	vm->cycles_to_die = CYCLE_TO_DIE;
	ft_bzero(&p, sizeof(t_process));
	ft_bzero(&g_memory, MEM_SIZE);
	ft_bzero(&g_reg, REG_NUMBER);
	ft_bzero(&g_memory_mark, MEM_SIZE);
	g_carrier = 0;
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

static int
	vm_populate_players(int i, char **av, t_vm *vm)
{
	int j;

	j = 0;
	while (vm->players[j])
		j++;
	if (j <= 4)
		vm->players[j] = av[i];
	else
		return (-1);
	return (0);
}

static int
	vm_get_champions(char **av, t_vm *vm)
{
	int i;
	int j;
	int equ;
	int num;

	i = 0;
	num = 0;
	while (av[++i])
	{
		j = -1;
		equ = 0;
		if (ft_strequ(&av[i][ft_strlen(av[i]) - 4], ".cor"))
		{
			while (++j < 4)
				if (ft_strequ(av[i], vm->players[j]) && av[i] == vm->players[j])
					equ = 1;
			if (!equ && vm_populate_players(i, av, vm) == -1)
				return (MAX_PLAYERS + 1);
			num++;
		}
	}
	vm->champ_size = num;
	return (num);
}

int
	main(int ac, char **av)
{
	t_vm			vm;
	int				i;

	ft_bzero(&vm, sizeof(t_vm));
	if (ac < 2 || vm_options(av, &vm) == -1)
		return (vm_print_usage(av, -1));
	if (vm_get_champions(av, &vm) > MAX_PLAYERS)
		return (vm_error(CHAMP_MAX, -1));
	i = -1;
	while (++i < vm.champ_size)
		if ((i = vm_read_binary(i, vm.players, &vm)) == -1)
			return (-1);
	vm_load_champs(&vm, g_memory);
	while (vm.cycles < vm.cycles_to_die)
	{
		(vm.v_lvl[V_LVL_0]) ? vm_print_memory_cursor(g_memory, vm) : 0;
		vm_decompiler(&vm);
		vm_executor(&vm);
		(vm.dump && vm.dump == vm.cycles) ? vm_print_memory(g_memory) : 0;
		if (vm.dump && vm.dump == vm.cycles)
			break ;
		vm.cycles++;
	}
	return (0);
}
