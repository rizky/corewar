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

int
	ft_cursor(t_process *p, int param1, int param2, int i)
{
	int cursor;

	if (p->op.params[i].type == DIR_CODE && p->op.params[i + 1].type
		== DIR_CODE)
		cursor = p->offset + p->pc + ((short)param1 + (short)param2) % IDX_MOD;
	else if (p->op.params[i].type == DIR_CODE)
		cursor = p->offset + p->pc + ((short)param1 + param2) % IDX_MOD;
	else if (p->op.params[i + 1].type == DIR_CODE)
		cursor = p->offset + p->pc + (param1 + (short)param2) % IDX_MOD;
	else
		cursor = p->offset + p->pc + (param1 + param2) % IDX_MOD;
	return (cursor);
}

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
		vm_binary_toint(&g_memory[(p->offset + p->pc + p->op.params[0].value) % MEM_SIZE], 2)
		: p->op.params[0].value;
	g_reg[p->champ][p->op.params[1].value] = (p->op.params[0].type == IND_CODE) ?
	(short)param0 : param0;
	if (param0 == 0)
		g_carry = 1;
	else
		g_carry = 0;
	vm_op_inc(vm, p);
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
	param0 = (p->op.params[0].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[0].value] : p->op.params[0].value;
	param1 = (p->op.params[1].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[1].value] : p->op.params[1].value;
	param0 = (p->op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p->offset + p->pc + p->op.params[0].value], 4)
		: param0;
	if (p->op.params[0].type == DIR_CODE && p->op.params[1].type == DIR_CODE)
		cursor = p->offset + p->pc + (((short)param0 + (short)param1));
	else if (p->op.params[0].type == DIR_CODE)
		cursor = p->offset + p->pc + (((short)param0 + param1));
	else if (p->op.params[1].type == DIR_CODE)
		cursor = p->offset + p->pc + ((param0 + (short)param1));
	else
		cursor = p->offset + p->pc + ((param0 + param1));
	cursor = cursor % MEM_SIZE;
	if (cursor < 0)
		cursor += MEM_SIZE;

	g_reg[p->champ][p->op.params[2].value] =
		vm_binary_toint(&g_memory[cursor], 4);
	vm_op_inc(vm, p);
}

void
	vm_op_lfork(t_vm *vm, t_process *p)
{
	t_process	new_p;
	int			value;

	ft_bzero(&new_p, sizeof(new_p));
	new_p.offset = p->champ * MEM_SIZE / vm->champ_size;
	new_p.champ = p->champ;
	value = (p->op.params[0].value + p->offset + p->pc);
	if (value > MEM_SIZE)
		value = value % MEM_SIZE;
	new_p.pc = p->pc + value - (p->offset + p->pc);
	new_p.champ = p->champ;
	fta_append(vm->champ[p->champ].processes, &new_p, 1);
	vm_op_inc(vm, p);
}

void
	vm_op_aff(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}
