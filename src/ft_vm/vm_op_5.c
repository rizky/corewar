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
	vm_op_fork(t_vm *vm, t_process *p)
{
	t_process	new_p;
	short		value;

	ft_bzero(&new_p, sizeof(new_p));
	new_p.offset = p->champ * MEM_SIZE / vm->champ_size;
	new_p.champ = p->champ;
	value = p->op.params[0].value;
	value = value % IDX_MOD;
	value += p->offset + p->pc;
	value = value % MEM_SIZE;
	new_p.pc = value - p->offset;
	if (value < 0)
		new_p.pc += MEM_SIZE;
	new_p.champ = p->champ;
	fta_append(vm->champ[p->champ].processes, &new_p, 1);
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
