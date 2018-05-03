/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:51:58 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/03 19:02:12 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_op_zjmp(t_vm *vm, t_process *p)
{
	short		value;

	(void)vm;
	if (p->carry)
	{
		value = p->op.params[0].value;
		value = value % IDX_MOD;
		value += p->offset + p->pc;
		value = value % MEM_SIZE;
		p->pc = value - p->offset;
		if (value < 0)
			p->pc += MEM_SIZE;
	}
	else
		vm_op_inc(vm, p);
}

void	vm_zjmp_print(t_process p)
{
	short	value;

	(void)p;
	value = (p.op.params[0].value + p.offset + p.pc);
	if (value > MEM_SIZE)
		value = (p.op.params[0].value + p.offset + p.pc) % MEM_SIZE;
	value = value - (p.offset + p.pc);
	if (value < 0)
		value += MEM_SIZE;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" %d", value);
	if (!p.carry)
		ft_printf(" FAILED");
	else
		ft_printf(" OK");
	ft_printf("\n");
}
