/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:23:54 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/04 22:17:05 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

static void
	vm_print_v_4(t_process p)
{
	if (p.op.opcode != 0)
		(((void (*)())g_op_dict[p.op.opcode].opprint)(p));
}

static void
	vm_print_v_16(t_process p)
{
	int i;
	int	size;

	if (p.op.opcode != 0 && (p.op.opcode != 9 || !p.carry))
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x) ",
			p.pc_next - p.pc,
			p.offset + p.pc,
			p.offset + p.pc_next);
		i = p.offset + p.pc;
		size = 0;
		while (size < p.pc_next - p.pc)
		{
			if (i == MEM_SIZE)
				i = 0;
			ft_printf("%02x ", g_memory[i]);
			i++;
			size++;
		}
		ft_printf("\n");
	}
}

static void
	vm_executor_op(t_vm *vm, t_process *p)
{
	t_process *prev_p;

	vm_decompiler_param(p, &(p->op));
	p->pc_next = p->pc + p->op.size;
	prev_p = ft_memalloc(sizeof(t_process));
	ft_memcpy(prev_p, p, sizeof(t_process));
	(vm->option_v[V_LVL_4]) ? vm_print_v_4(*p) : 0;
	(((void (*)())g_op_dict[p->op.opcode].opfunc)(vm, p));
	(vm->option_v[V_LVL_16]) ? vm_print_v_16(*prev_p) : 0;
	free(prev_p);
	ft_bzero(&(p->op), sizeof(t_op));
}

void
	vm_executor(t_vm *vm)
{
	int			i;
	t_process	*p;
	t_op		op;

	g_cycles++;
	g_cycles_to++;
	(vm->option_v[V_LVL_2]) ? ft_printfln("It is now cycle %d", g_cycles) : 0;
	i = (int)(vm->processes.size) - 1;
	while (i >= 0)
	{
		ft_bzero(&op, sizeof(t_op));
		p = &(((t_process*)vm->processes.data)[i]);
		if (p->op.opcode == 0)
		{
			p->cycles = g_cycles;
			vm_decompiler_op(vm, p, &op);
			p->op = op;
		}
		if (p->cycles == g_cycles)
		{
			vm_executor_op(vm, p);
			(((t_process*)vm->processes.data)[i]) = *p;
		}
		i--;
	}
	(vm->dump == 1 && vm->cycles == g_cycles) ? vm_print_memory() : 0;
	(vm->dump == 2 && vm->cycles == g_cycles) ? vm_print_memory_color(*vm) : 0;
	(vm->option_g[VISU_1]) ? vm_print_memory_cursor(*vm) : 0;
}
