/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:23:14 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/26 08:42:45 by fpetras          ###   ########.fr       */
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
