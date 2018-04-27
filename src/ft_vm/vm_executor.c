/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:23:54 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/27 05:06:19 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

static void
	vm_print_v_4(t_process p, int n)
{
	if (p.op.opcode != 0)
	{
		ft_printf("P %4d | ", n);
		(((void (*)())g_op_dict[p.op.opcode].opprint)(p));
		n--;
	}
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
	int			n;

	i = vm->champ_size - 1;
	n = vm->process_size;
	while (i >= 0)
	{
		j = -1;
		while (++j < (int)(vm->champ[i].processes->size))
		{
			p = &(((t_process*)vm->champ[i].processes->data)[j]);
			if (p->cycles == g_cycles)
			{
				(vm->v_lvl[V_LVL_4]) ? vm_print_v_4(*p, n) : 0;
				(vm->v_lvl[V_LVL_16]) ? vm_print_v_16(*p) : 0;
				(((void (*)())g_op_dict[p->op.opcode].opfunc)(vm, p));
				ft_bzero(&(p->op), sizeof(t_op));
			}
		}
		i--;
		n--;
	}
}
