/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 08:27:57 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/27 03:26:43 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_op_inc(t_vm *vm, t_process *p)
{
	(void)vm;
	if (p->op.opcode != 0)
		p->pc = p->pc_next;
	else
		p->pc++;
	if (p->pc + p->offset == MEM_SIZE)
		p->pc = p->offset * -1;
}

void	vm_op_live(t_vm *vm, t_process *p)
{
	(void)vm;
	p->live_nbr++;
	vm_op_inc(vm, p);
}

void	vm_op_ld(t_vm *vm, t_process *p)
{
	int		param0;

	(void)vm;
	param0 = (p->op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p->offset + p->pc + p->op.params[0].value], 4)
		: p->op.params[0].value;
	g_reg[p->champ][p->op.params[1].value] = param0;
	vm_op_inc(vm, p);
}

void	vm_op_st(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}

void	vm_op_add(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}
