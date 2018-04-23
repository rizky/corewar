/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:23:14 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/23 19:23:33 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_op_inc(t_vm *vm, t_process *p, t_op *op)
{
	(void)vm;
	(void)op;
	p->pc++;
}

void
	vm_op_sti(t_vm *vm, t_process *p, t_op *op)
{
	(void)vm;
	(void)op;
	p->pc += 2;
}
