/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:23:14 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/24 17:21:43 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

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
	(void)vm;
	vm_op_inc(vm, p);
}