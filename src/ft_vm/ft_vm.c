/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:38:33 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/24 01:16:10 by rnugroho         ###   ########.fr       */
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
	vm_get_champions(char **av, t_vm *vm)
{
	int i;
	int j;
	int equ;
	int num;

	i = 0;
	equ = 0;
	num = 0;
	while (av[++i])
	{
		j = -1;
		equ = 0;
		if (ft_strequ(&av[i][ft_strlen(av[i]) - 4], ".cor"))
		{
			while (++j < 4)
				if (ft_strequ(av[i], vm->players[j]))
					equ = 1;
			j = 0;
			if (!equ)
			{
				while (vm->players[j])
					j++;
				if (j <= 4)
					vm->players[j] = av[i];
				else
					return (MAX_PLAYERS + 1);
			}
			num++;
		}
	}
	vm->champ_size = num;
	return (num);
}

void
	vm_print_v_4(t_vm vm)
{
	int		i;
	int		j;
	int		k;
	t_op	op;

	i = vm.champ_size - 1;
	while (i >= 0)
	{
		j = -1;
		while (++j < (int)(vm.champ[i].processes->size))
		{
			op = (((t_process*)vm.champ[i].processes->data)[j]).op;
			if (op.opcode != 0)
			{
				ft_printf("P %3d | %s", j + 1, g_op_dict[op.opcode].name);
				k = 0;
				while (k < op.param_c)
				{
					if (op.params[k].type == REG_CODE)
						ft_printf(" r%d", op.params[k].value);
					else
						ft_printf(" %d", op.params[k].value);
					k++;
				}
				ft_printf("\n");
			}
		}
		i--;
	}
}

int
	main(int ac, char **av)
{
	t_vm			vm;
	int				i;
	time_t		start;						//count the time to repeat the music, can decide if want to include this inside t_vm

	ft_bzero(&g_memory, MEM_SIZE);
	ft_bzero(&g_memory_mark, MEM_SIZE);
	ft_bzero(&vm, sizeof(t_vm));
	if (ac < 2 || vm_options(av, &vm) == -1)
	{
		ft_dprintf(2, "usage: %s [-dump nbr_cycles] [-n number] ", av[0]);
		ft_dprintf(2, "champion1.cor ...\n");
		return (-1);
	}
	else if (vm_get_champions(av, &vm) > MAX_PLAYERS)
	{
		ft_dprintf(2, "Too many champions\n");
		return (-1);
	}
	i = -1;
	while (++i < vm.champ_size)
		if ((i = vm_read_binary(i, vm.players, &vm)) == -1)
			return (-1);
	vm_load_champs(&vm, g_memory);
	// if (option == "-v")					// this is the dummy code, i dunno how the vm_options will handle this option yet
	init_ncurses(&vm);						// if option contain -v call this function
	start = time(NULL);						//count the time to repeat the music
	while (vm.cycles < vm.cycles_to_die)
	{
		// if (vm.status.pause == 0)		// we can leave this here, by default pause is 0, even withoout option -v, this won't affect the program
		// {
			// if (option == "-v")			// this is the dummy code, i dunno how the vm_options will handle this option yet
			// {
				if (time(NULL) - start >= 121)
				{
					system("afplay -t 120 sound/nyan.mp3&");
					start = time(NULL);
				}
				draw(&vm);
				if ((key_hook(&vm.status)) == -1)
					break ;
				usleep(vm.status.delay);
			// }


			// vm_print_memory_cursor(g_memory, vm);
			vm_executor(&vm);
			vm_print_v_4(vm);
			vm.cycles++;
		// }
	}
	// if (option == "-v")					// this is the dummy code, i dunno how the vm_options will handle this option yet
	draw_end(&vm.win);
	return (0);
}
