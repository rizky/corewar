/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 08:30:28 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/27 04:34:21 by fpetras          ###   ########.fr       */
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
		vm_binary_toint(&g_memory[(p->offset + p->pc + p->op.params[0].value)
			% MEM_SIZE], 2)
		: p->op.params[0].value;
	g_reg[p->champ][p->op.params[1].value] = (p->op.params[0].type == IND_CODE)
	? (short)param0 : param0;
	if (param0 == 0)
		g_carry = 1;
	else
		g_carry = 0;
	vm_op_inc(vm, p);
}

int
	ft_init_param_long(t_process *p, int i)
{
	int			result;

	result = (p->op.params[i].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[i].value] : p->op.params[i].value;
	result = (p->op.params[i].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p->offset + p->pc + p->op.params[i].value], 4)
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
	param1 = ft_init_param_long(p, 1);
	param0 = (p->op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p->offset + p->pc + p->op.params[0].value], 4)
		: param0;
	cursor = ft_cursor_long(p, param0, param1, 0) % MEM_SIZE;
	if (cursor < 0)
		cursor += MEM_SIZE;
	g_reg[p->champ][p->op.params[2].value] =
		vm_binary_toint(&g_memory[cursor], 4);
	vm_op_inc(vm, p);
}
