/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:50:31 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/03 11:23:25 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_op_or(t_vm *vm, t_process *p)
{
	int		param0;
	int		param1;

	(void)vm;
	if (p->op.params[2].value < 1 || p->op.params[2].value > 16 ||
	((p->op.params[1].type == REG_CODE) && (p->op.params[1].value < 1 ||
	p->op.params[1].value > 16)) || ((p->op.params[0].type == REG_CODE) &&
	(p->op.params[0].value < 1 || p->op.params[0].value > 16)))
	{
		vm_op_inc(vm, p);
		return ;
	}
	param0 = (p->op.params[0].type == REG_CODE) ?
		p->reg[p->op.params[0].value] : p->op.params[0].value;
	param1 = (p->op.params[1].type == REG_CODE) ?
		p->reg[p->op.params[1].value] : p->op.params[1].value;
	param0 = (p->op.params[0].type == IND_CODE) ?
		vm_ld_mem((p->offset + p->pc +
		(p->op.params[0].value % IDX_MOD)) % MEM_SIZE, 4) : param0;
	param1 = (p->op.params[1].type == IND_CODE) ?
		vm_ld_mem((p->offset + p->pc +
		(p->op.params[1].value % IDX_MOD)) % MEM_SIZE, 4) : param1;
	p->reg[p->op.params[2].value] = param0 | param1;
	p->carry = (p->reg[p->op.params[2].value] == 0) ? 1 : 0;
	vm_op_inc(vm, p);
}

void	vm_or_print(t_process p)
{
	if (p.op.params[2].value < 1 || p.op.params[2].value > 16 ||
		((p.op.params[1].type == REG_CODE) &&
			(p.op.params[1].value < 1 || p.op.params[1].value > 16)) ||
		((p.op.params[0].type == REG_CODE) &&
			(p.op.params[0].value < 1 || p.op.params[0].value > 16)))
		return ;
	(void)p;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	if (p.op.params[0].type == REG_CODE)
		ft_printf(" %d", p.reg[p.op.params[0].value]);
	else if (p.op.params[0].type == IND_CODE)
		ft_printf(" %d", vm_ld_mem((p.offset +
			p.pc + (p.op.params[0].value % IDX_MOD)) % MEM_SIZE, 4));
	else
		ft_printf(" %d", p.op.params[0].value);
	if (p.op.params[1].type == REG_CODE)
		ft_printf(" %d", p.reg[p.op.params[1].value]);
	else if (p.op.params[1].type == IND_CODE)
		ft_printf(" %d", vm_ld_mem((p.offset +
			p.pc + (p.op.params[0].value % IDX_MOD)) % MEM_SIZE, 4));
	else
		ft_printf(" %d", p.op.params[1].value);
	ft_printf(" r%d", p.op.params[2].value);
	ft_printf("\n");
}
