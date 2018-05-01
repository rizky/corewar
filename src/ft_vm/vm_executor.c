/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:23:54 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/02 00:41:38 by rnugroho         ###   ########.fr       */
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

	if (p.op.opcode != 0)
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x) ",
					p.pc_next - p.pc, p.pc, p.pc_next);
		i = p.pc;
		while (i < p.pc_next)
			ft_printf("%02x ", g_memory[i++]);
		ft_printf("\n");
	}
}

void
	vm_executor(t_vm *vm)
{
	int			i;
	int			j;
	t_process	*p;

	i = vm->champ_size - 1;
	vm_decompiler(vm);
	(vm->v_lvl[V_LVL_2]) ? ft_printfln("It is now cycle %d", g_cycles) : 0;
	while (i >= 0)
	{
		j = -1;
		while (++j < (int)(vm->champ[i].processes->size))
		{
			p = &(((t_process*)vm->champ[i].processes->data)[j]);
			if (p->cycles == g_cycles)
			{
				if (vm_decompiler_param(p, &(p->op)) == -1)
				{
					ft_bzero(&(p->op), sizeof(t_op));
					p->pc += 2;
					if (p->pc + p->offset >= MEM_SIZE)
						p->pc = p->offset * -1;
					break ;
				}
				p->pc_next = ((p->pc + p->op.size) >= MEM_SIZE) ?
					(p->pc + p->op.size) * -1 :
					p->pc + p->op.size;
				(vm->v_lvl[V_LVL_4]) ? vm_print_v_4(*p) : 0;
				(vm->v_lvl[V_LVL_16]) ? vm_print_v_16(*p) : 0;
				(((void (*)())g_op_dict[p->op.opcode].opfunc)(vm, p));
				ft_bzero(&(p->op), sizeof(t_op));
			}
		}
		i--;
	}
	(vm->dump && vm->cycles == g_cycles) ? vm_print_memory(g_memory) : 0;
	(vm->v_lvl[V_LVL_0]) ? vm_print_memory_cursor(g_memory, *vm) : 0;
}
