/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 08:29:55 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/27 16:28:32 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_op_zjmp(t_vm *vm, t_process *p)
{
	short value;

	(void)vm;
	
	if (g_carry)
	{
		// value = p->op.params[0].value;
		// value = value % IDX_MOD;
		// value += p->offset + p->pc;
		// value = ((p->op.params[0].value + p->offset + p->pc) %IDX_MOD);
		// // if (value > MEM_SIZE)
		// value = value % MEM_SIZE;
		// p->pc += value - (p->offset + p->pc);
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

// void	vm_op_ldi_d2(t_process *p, int *cursor)
// {
// 	short	param0;

// 	param0 = p->op.params[0].value;
// 	*cursor = (p->offset + p->pc + param0 + (short)p->op.params[1].value) % IDX_MOD;
// }

void	vm_op_ldi(t_vm *vm, t_process *p)
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
		vm_binary_toint(&g_memory[(p->offset + p->pc + p->op.params[0].value) % IDX_MOD], 4)
		: param0;
	if (p->op.params[0].type == DIR_CODE && p->op.params[1].type == DIR_CODE)
		cursor = (p->offset + p->pc + (short)param0 + (short)param1) % IDX_MOD;
	else if (p->op.params[0].type == DIR_CODE)
		cursor = (p->offset + p->pc + (short)param0 + param1) % IDX_MOD;
	else if (p->op.params[1].type == DIR_CODE)
		cursor = (p->offset + p->pc + param0 + (short)param1) % IDX_MOD;
	else
		cursor = (p->offset + p->pc + param0 + param1) % IDX_MOD;
	if (cursor < 0)
		cursor += MEM_SIZE;
	g_reg[p->champ][p->op.params[2].value] =
		vm_binary_toint(&g_memory[cursor], 4);
	vm_op_inc(vm, p);
}

void	vm_op_sti(t_vm *vm, t_process *p)
{
	int		param1;
	int		param2;
	int		cursor;
	char	*temp;

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
	param1 = (p->op.params[1].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[1].value] : p->op.params[1].value;
	param2 = (p->op.params[2].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[2].value] : p->op.params[2].value;
	param1 = (p->op.params[1].type == IND_CODE) ?
		vm_binary_toint(&g_memory[(p->offset + p->pc + p->op.params[1].value) % IDX_MOD], 4)
		: param1;
	if (p->op.params[1].type == DIR_CODE && p->op.params[2].type == DIR_CODE)
		cursor = (p->offset + p->pc + (short)param1 + (short)param2) % IDX_MOD;
	else if (p->op.params[1].type == DIR_CODE)
		cursor = (p->offset + p->pc + (short)param1 + param2) % IDX_MOD;
	else if (p->op.params[2].type == DIR_CODE)
		cursor = (p->offset + p->pc + param1 + (short)param2) % IDX_MOD;
	else
		cursor = (p->offset + p->pc + param1 + param2) % IDX_MOD;
	temp = vm_to_big_endian(g_reg[p->champ][p->op.params[0].value], 4);
	ft_memcpy(&g_memory[cursor], temp, 4);
	vm_memmark(&g_memory_mark[cursor], p->champ + 1, 4);
	free(temp);
	vm_op_inc(vm, p);
}

void
	vm_op_fork(t_vm *vm, t_process *p)
{
	t_process	new_p;
	short		value;

	ft_bzero(&new_p, sizeof(new_p));
	new_p.offset = p->champ * MEM_SIZE / vm->champ_size;
	new_p.champ = p->champ;
//	if (p->op.params[0].value > IDX_MOD)
	value = p->op.params[0].value;
	value = value % IDX_MOD;
	value += p->offset + p->pc;
//	if (value > MEM_SIZE)
	value = value % MEM_SIZE;
	new_p.pc = value - p->offset;
	if (value < 0)
		new_p.pc += MEM_SIZE;
	new_p.champ = p->champ;
	//vm->champ[p->champ].processes->size += 1;
	//vm->process_size += 1;
	fta_append(vm->champ[p->champ].processes, &new_p, 1);
	vm_op_inc(vm, p);
}


