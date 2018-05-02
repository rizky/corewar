/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 08:29:55 by fpetras           #+#    #+#             */
/*   Updated: 2018/05/01 21:32:50 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_op_zjmp(t_vm *vm, t_process *p)
{
	short		value;

	(void)vm;
	if (g_carry)
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

int
	ft_init_param(t_process *p, int i)
{
	int			result;

	result = (p->op.params[i].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[i].value] : p->op.params[i].value;
	result = (p->op.params[i].type == IND_CODE) ?
		vm_ld_mem((p->offset + p->pc +
			(p->op.params[0].value % IDX_MOD)) % MEM_SIZE, 4) : result;
	return (result);
}

int
	ft_cursor(t_process *p, int param1, int param2, int i)
{
	int cursor;

	if (p->op.params[i].type == DIR_CODE && p->op.params[i + 1].type
		== DIR_CODE)
		cursor = p->offset + p->pc + (((short)param1 + (short)param2) % IDX_MOD);
	else if (p->op.params[i].type == DIR_CODE)
		cursor = p->offset + p->pc + (((short)param1 + param2) % IDX_MOD);
	else if (p->op.params[i + 1].type == DIR_CODE)
		cursor = p->offset + p->pc + ((param1 + (short)param2) % IDX_MOD);
	else
		cursor = p->offset + p->pc + ((param1 + param2) % IDX_MOD);
	return (cursor);
}

void
	vm_op_ldi(t_vm *vm, t_process *p)
{
	int			param0;
	int			param1;
	int			cursor;

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
	param0 = ft_init_param(p, 0);
	param1 = (p->op.params[1].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[1].value] : p->op.params[1].value;
	cursor = ft_cursor(p, param0, param1, 0) % MEM_SIZE;
	if (cursor < 0)
		cursor += MEM_SIZE;
	g_reg[p->champ][p->op.params[2].value] = vm_ld_mem(cursor, 4);
	vm_op_inc(vm, p);
}

void
	vm_op_sti(t_vm *vm, t_process *p)
{
	int			param1;
	int			param2;
	int			cursor;
	char		*temp;

	(void)vm;
	if (p->op.params[0].value < 1 || p->op.params[0].value > 16 ||
		((p->op.params[1].type == REG_CODE) &&
			(p->op.params[1].value < 1 || p->op.params[1].value > 16)) ||
		((p->op.params[2].type == REG_CODE) &&
			(p->op.params[2].value < 1 || p->op.params[2].value > 16)))
	{
		vm_op_inc(vm, p);
		return ;
	}
	param1 = ft_init_param(p, 1);
	param2 = (p->op.params[2].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[2].value] : p->op.params[2].value;
	cursor = ft_cursor(p, param1, param2, 1) % MEM_SIZE;
	if (cursor < 0)
		cursor += MEM_SIZE;
	temp = vm_to_big_endian(g_reg[p->champ][p->op.params[0].value], 4);
	vm_st_mem(cursor, temp, p->champ, 4);
	free(temp);
	vm_op_inc(vm, p);
}
