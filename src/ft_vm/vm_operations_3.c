/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 08:29:55 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/26 08:39:40 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_op_zjmp(t_vm *vm, t_process *p)
{
	int value;

	(void)vm;
	value = (p->op.params[0].value + p->offset + p->pc);
	if (value > MEM_SIZE)
		value = value % MEM_SIZE;
	if (g_carry)
		p->pc += value - (p->offset + p->pc);
	else
		vm_op_inc(vm, p);
}

void	vm_op_ldi(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}

void	vm_op_sti(t_vm *vm, t_process *p)
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
 	vm_op_fork(t_vm *vm, t_process *p)
 {
 	t_process	new_p;
	 int value;

	new_p.offset = p->champ * MEM_SIZE / vm->champ_size;
	new_p.champ = p->champ;
	value = (p->op.params[0].value + p->offset + p->pc);
	if (value > MEM_SIZE)
		value = value % MEM_SIZE;
	 new_p.pc = p->pc + value - (p->offset + p->pc);
	fta_append(vm->champ[p->champ].processes, &new_p, 1);
 }
