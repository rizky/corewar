/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 08:30:28 by fpetras           #+#    #+#             */
/*   Updated: 2018/05/01 15:12:43 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_op_lld(t_vm *vm, t_process *p)
{
	int		param0;

	(void)vm;
	if (p->op.params[1].value < 1 || p->op.params[1].value > 16)
	{
		vm_op_inc(vm, p);
		return ;
	}
	param0 = (p->op.params[0].type == IND_CODE) ?
		vm_ld_mem((p->offset + p->pc + p->op.params[0].value) % MEM_SIZE, 2)
		: p->op.params[0].value;
	p->reg[p->op.params[1].value] = (p->op.params[0].type == IND_CODE)
	? (short)param0 : param0;
	if (param0 == 0)
		p->carry = 1;
	else
		p->carry = 0;
	vm_op_inc(vm, p);
}

int
	ft_init_param_long(t_process *p, int i)
{
	int			result;

	result = (p->op.params[i].type == REG_CODE) ?
		p->reg[p->op.params[i].value] : p->op.params[i].value;
	result = (p->op.params[i].type == IND_CODE) ?
		vm_ld_mem(p->offset + p->pc + p->op.params[i].value, 4)
		: result;
	return (result);
}

int
	ft_cursor_long(t_process *p, int param1, int param2, int i)
{
	int cursor;

	if (p->op.params[i].type == DIR_CODE && p->op.params[i + 1].type
		== DIR_CODE)
		cursor = p->offset + p->pc + ((short)param1 + (short)param2);
	else if (p->op.params[i].type == DIR_CODE)
		cursor = p->offset + p->pc + ((short)param1 + param2);
	else if (p->op.params[i + 1].type == DIR_CODE)
		cursor = p->offset + p->pc + (param1 + (short)param2);
	else
		cursor = p->offset + p->pc + (param1 + param2);
	return (cursor);
}

void
	vm_op_lldi(t_vm *vm, t_process *p)
{
	int		param0;
	int		param1;
	int		cursor;

	(void)vm;
	if (p->op.params[2].value < 1 || p->op.params[2].value > 16 ||
		((p->op.params[1].type == REG_CODE) &&
			(p->op.params[1].value < 1 || p->op.params[1].value > 16)) ||
		((p->op.params[0].type == REG_CODE) &&
			(p->op.params[0].value < 1 || p->op.params[0].value > 16)))
	{
		vm_op_inc(vm, p);
		return ;
	}
	param0 = ft_init_param_long(p, 0);
	param1 = (p->op.params[1].type == REG_CODE) ?
		p->reg[p->op.params[1].value] : p->op.params[1].value;
	cursor = ft_cursor_long(p, param0, param1, 0) % MEM_SIZE;
	(cursor < 0) ? cursor += MEM_SIZE : 0;
	p->reg[p->op.params[2].value] = vm_ld_mem(cursor, 4);
	p->carry = (p->reg[p->op.params[2].value] == 0) ? 1 : 0;
	vm_op_inc(vm, p);
}
