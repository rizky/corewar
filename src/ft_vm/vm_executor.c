/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:23:54 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/24 19:25:10 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_executor(t_vm *vm)
{
	int			i;
	int			j;
	t_process	*p;
	int			n;

	i = vm->champ_size - 1;
	n = vm->process_size;
	while (i >= 0)
	{
		j = -1;
		while (++j < (int)(vm->champ[i].processes->size))
		{
			p = &(((t_process*)vm->champ[i].processes->data)[j]);
			vm_print_v_4(*p, n);
			(((void (*)())g_op_dict[p->op.opcode].opfunc)(vm, p));
		}
		i--;
		n--;
	}
}

void
	vm_print_v_4(t_process p, int n)
{
	if (p.op.opcode != 0)
	{
		ft_printf("P %3d | ", n);
		(((void (*)())g_op_dict[p.op.opcode].opprint)(p));
		n--;
	}
}
