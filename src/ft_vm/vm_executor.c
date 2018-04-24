/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:23:54 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/24 19:11:49 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_executor(t_vm *vm)
{
	int			i;
	int			j;
	t_process	*p;

	i = vm->champ_size - 1;
	while (i >= 0)
	{
		j = -1;
		while (++j < (int)(vm->champ[i].processes->size))
		{
			p = &(((t_process*)vm->champ[i].processes->data)[j]);
			(((void (*)())g_op_dict[p->op.opcode].opfunc)(vm, p));
		}
		i--;
	}
}

void
	vm_print_v_4(t_vm vm)
{
	int		i;
	int		j;
	t_op	op;

	i = vm.champ_size - 1;
	while (i >= 0)
	{
		j = -1;
		while (++j < (int)(vm.champ[i].processes->size))
		{
			op = (((t_process*)vm.champ[i].processes->data)[j]).op;
			if (op.opcode != 0)
			{
				ft_printf("P %3d | ", j + 1);
				(((void (*)())g_op_dict[op.opcode].opprint)(
					((t_process*)vm.champ[i].processes->data)[j]));
			}
		}
		i--;
	}
}
