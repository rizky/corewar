/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:23:14 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/25 13:58:45 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

char
	*vm_to_big_endian(int value, int size)
{
	t_array	result;
	int		i;
	int		bits;

	i = 0;
	result = NEW_ARRAY(char);
	bits = size * 8;
	while (i <= bits - 8)
	{
		fta_append_char(&result, value >> (bits - 8 - i));
		i = i + 8;
	}
	return (result.data);
}

void
	vm_op_inc(t_vm *vm, t_process *p)
{
	(void)vm;
	if (p->op.opcode != 0)
		p->pc = p->pc_next;
	else
		p->pc++;
	if (p->pc + p->offset == MEM_SIZE)
		p->pc = p->offset * -1;
}

void
	vm_op_sti(t_vm *vm, t_process *p)
{
	int		param1;
	int		param2;
	char	*temp;

	(void)vm;
	param1 = (p->op.params[1].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[1].value] : p->op.params[1].value;
	param2 = (p->op.params[2].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[2].value] : p->op.params[2].value;
	temp = vm_to_big_endian(g_reg[p->champ][p->op.params[0].value], 4);
	ft_memcpy(&g_memory[p->offset + p->pc + param1 + param2],
		temp, 4);
	vm_memmark(&g_memory_mark[p->offset + p->pc + param1 + param2],
		p->champ + 1, 4);
	free(temp);
	vm_op_inc(vm, p);
}

void
	vm_op_and(t_vm *vm, t_process *p)
{
	int		param0;
	int		param1;

	(void)vm;
	param0 = (p->op.params[0].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[0].value] : p->op.params[0].value;
	param1 = (p->op.params[1].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[1].value] : p->op.params[1].value;
	g_reg[p->champ][p->op.params[2].value] = param0 & param1;
	if (g_reg[p->champ][p->op.params[2].value] == 0)
		g_carrier = 1;
	vm_op_inc(vm, p);
}

void
	vm_op_live(t_vm *vm, t_process *p)
{
	(void)vm;
	p->live_nbr++;
	vm_op_inc(vm, p);
}

void
	vm_op_zjmp(t_vm *vm, t_process *p)
{
	int value;

	(void)vm;
	value = (p->op.params[0].value + p->offset + p->pc);
	if (value > MEM_SIZE)
		value = value % MEM_SIZE;
	if (g_carrier)
		p->pc += value - (p->offset + p->pc);
}
