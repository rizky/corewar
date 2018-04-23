/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:23:54 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/23 12:31:55 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_op_inc(t_vm *vm, t_process *p)
{
	(void)vm;
	p->pc++;
}

void
	vm_executor_process(t_vm *vm, t_process *p)
{
	(((void (*)())g_op_dict[g_memory[p->offset + p->pc]].opfunc)(vm, p));
}

void
	vm_executor(t_vm *vm)
{
	int		i;
	int		j;

	i = 0;
	while (i < vm->champ_size)
	{
		j = 0;
		while (j < (int)(vm->champ[j].processes->size))
		{
			vm_executor_process(vm,
				&(((t_process*)vm->champ[i].processes->data)[j]));
			j++;
		}
		i++;
	}
}
