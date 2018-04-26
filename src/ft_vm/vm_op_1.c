/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 08:27:57 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/27 01:55:01 by rnugroho         ###   ########.fr       */
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

void	vm_op_live(t_vm *vm, t_process *p)
{
	(void)vm;
	p->live_nbr++;
	vm_op_inc(vm, p);
}

void	vm_op_ld(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
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
