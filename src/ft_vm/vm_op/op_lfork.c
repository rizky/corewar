/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:00:19 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/02 19:00:06 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_op_lfork(t_vm *vm, t_process *p)
{
	t_process	new_p;
	int			value;

	ft_bzero(&new_p, sizeof(new_p));
	new_p.offset = p->champ * MEM_SIZE / vm->champ_size;
	new_p.champ = p->champ;
	new_p.live_nbr = p->live_nbr;
	new_p.carry = p->carry;
	ft_memcpy(new_p.reg, p->reg, REG_NUMBER);
	value = (p->op.params[0].value + p->offset + p->pc);
	value = value % MEM_SIZE;
	new_p.pc = value - p->offset;
	if (value < 0)
		new_p.pc += MEM_SIZE;
	new_p.index = vm->process_index++;
	fta_append(&(vm->processes), &new_p, 1);
	vm_op_inc(vm, p);
}

// void
// 	vm_lfork_print(t_process p)
// {
// 	ft_printf("P %4d | ", p.champ + 1);
// 	ft_printf("%s", g_op_dict[p.op.opcode].name);
// 	ft_printf(" %hd (%d)", p.op.params[0].value, p.pc + p.op.params[0].value);
// 	ft_printf("\n");
// }

void
	vm_lfork_print(t_process p)
{
	int value;

	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	value = p.pc + p.offset + p.op.params[0].value;
	if (value > MEM_SIZE)
		value = value % MEM_SIZE;
	ft_printf(" %hd (%hd)", p.op.params[0].value,
		p.pc + p.offset + p.op.params[0].value);
	ft_printf("\n");
}

