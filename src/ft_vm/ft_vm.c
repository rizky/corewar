/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:38:33 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/02 16:34:24 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"
#include "ft_vm_draw.h"

void
	vm_free(t_vm *vm)
{
	int i;

	i = 0;
	while (i < vm->champ_size)
	{
		free(vm->champ[i].op);
		fta_clear(&(vm->processes));
		i++;
	}
}

void
	vm_load_champs(t_vm *vm, unsigned char memory[MEM_SIZE])
{
	int			i;
	t_process	p;

	i = -1;
	vm_init_g_var();
	ft_bzero(&p, sizeof(t_process));
	ft_printfln("Introducing contestants...");
	while (++i < vm->champ_size)
	{
		ft_printfln("* Player %d, weighing %d %s, \"%s\" (\"%s\") !", i + 1,
			vm->champ[i].header.prog_size, (vm->champ[i].header.prog_size > 1) ?
			"bytes" : "byte", vm->champ[i].header.prog_name,
			vm->champ[i].header.comment);
		ft_memcpy(&memory[i * MEM_SIZE / vm->champ_size], vm->champ[i].op,
			vm->champ[i].header.prog_size);
		vm_memmark(&g_memory_mark[i * MEM_SIZE / vm->champ_size], i + 1,
			vm->champ[i].header.prog_size);
		p.offset = i * MEM_SIZE / vm->champ_size;
		p.champ = i;
		p.index = 1 + vm->processes.size;
		p.reg[1] = (i + 1) * -1;
		fta_append(&(vm->processes), &p, 1);
	}
}

static int
	vm_populate_players(int i, char **av, t_vm *vm)
{
	int j;

	j = 0;
	while (vm->players[j])
		j++;
	if (j < 4)
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
				return (vm->champ_size = MAX_PLAYERS + 1);
			num++;
		}
	}
	if (num < 1 || num > MAX_PLAYERS)
		return (-1);
	return (num);
}

int
	main(int ac, char **av)
{
	t_vm		vm;
	time_t		start;
	t_array	processes;

	ft_bzero(&vm, sizeof(t_vm));
	processes = NEW_ARRAY(t_process);
	vm.processes = processes;
	if (ac < 2 || vm_options(av, &vm) == -1)
		return (vm_print_usage(av, -1));
	if ((vm.champ_size = vm_get_champions(av, &vm)) == -1)
		return (vm_error(vm.champ_size < 1 ? CHAMP_MIN : CHAMP_MAX, -1, NULL));
	if (vm_read_binaries(vm.players, &vm) == -1)
		return (-1);
	vm_load_champs(&vm, g_memory);
	while (vm_checker(&vm))
	{
		g_cycles++;
		g_cycles_to++;
		vm_executor(&vm);
		if (vm.v_lvl[V_LVL_1] && vm_start_ncurse(&start, vm) == -1)
			break ;
	}
	(!vm.dump || g_cycles < vm.cycles) ?
	ft_printfln("Contestant %d, \"%s\", has won !",
		vm.winner + 1, vm.champ[vm.winner].header.prog_name) : 0;
	(vm.v_lvl[V_LVL_1]) ? draw_end(&g_draw_win) : 0;
	vm_free(&vm);
	return (0);
}
