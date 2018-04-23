/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:23:54 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/23 11:24:27 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_executor_process(t_vm *vm, t_process *p)
{
	p->pc++;
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
