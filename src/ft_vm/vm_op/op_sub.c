/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:49:11 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/03 11:22:59 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_op_sub(t_vm *vm, t_process *p)
{
	(void)vm;
	if (p->op.params[0].value < 1 ||
		p->op.params[0].value > 16 ||
		p->op.params[1].value < 1 ||
		p->op.params[1].value > 16 ||
		p->op.params[2].value < 1 ||
		p->op.params[2].value > 16)
	{
		vm_op_inc(vm, p);
		return ;
	}
	p->reg[p->op.params[2].value] =
		p->reg[p->op.params[0].value] -
		p->reg[p->op.params[1].value];
	if (p->reg[p->op.params[2].value] == 0)
		p->carry = 1;
	else
		p->carry = 0;
	vm_op_inc(vm, p);
}

void	vm_sub_print(t_process p)
{
	if (p.op.params[0].value < 1 ||
		p.op.params[0].value > 16 ||
		p.op.params[1].value < 1 ||
		p.op.params[1].value > 16 ||
		p.op.params[2].value < 1 ||
		p.op.params[2].value > 16)
		return ;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" r%d", p.op.params[0].value);
	ft_printf(" r%d", p.op.params[1].value);
	ft_printf(" r%d", p.op.params[2].value);
	ft_printf("\n");
}
