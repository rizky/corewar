/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:46:49 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/05 16:05:10 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_op_ld(t_vm *vm, t_process *p)
{
	int		param0;
	int		val;

	(void)vm;
	if (p->op.params[1].value < 1 || p->op.params[1].value > 16 ||
		p->op.params[0].type == 0)
	{
		vm_op_inc(vm, p);
		return ;
	}
	val = p->op.params[0].value % IDX_MOD;
	val = (p->offset + p->pc + (val)) % MEM_SIZE;
	if (val < 0)
		val = MEM_SIZE + val;
	param0 = (p->op.params[0].type == IND_CODE) ?
		vm_ld_mem(val, 4) : p->op.params[0].value;
	p->reg[p->op.params[1].value] = param0;
	if (param0 == 0)
		p->carry = 1;
	else
		p->carry = 0;
	vm_op_inc(vm, p);
}

void	vm_ld_print(t_process p)
{
	int param0;
	int	val;

	if (p.op.params[1].value < 1 || p.op.params[1].value > 16 ||
		p.op.params[0].type == 0)
		return ;
	val = p.op.params[0].value % IDX_MOD;
	val = (p.offset + p.pc + (val)) % MEM_SIZE;
	if (val < 0)
		val = MEM_SIZE + val;
	param0 = (p.op.params[0].type == IND_CODE) ?
		vm_ld_mem(val, 4) : p.op.params[0].value;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" %d", param0);
	ft_printf(" r%d", p.op.params[1].value);
	ft_printf("\n");
}
