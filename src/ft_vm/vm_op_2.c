/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 08:29:15 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/27 14:57:30 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_op_sub(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}

void	vm_op_and(t_vm *vm, t_process *p)
{
	(void)vm;
	if (g_reg[p->champ][p->op.params[0].value] < 1 ||
		g_reg[p->champ][p->op.params[0].value] > 16 ||
		g_reg[p->champ][p->op.params[1].value] < 1 ||
		g_reg[p->champ][p->op.params[1].value] > 16 ||
		g_reg[p->champ][p->op.params[2].value] < 1 ||
		g_reg[p->champ][p->op.params[2].value] > 16)
		vm_op_inc(vm, p);
	g_reg[p->champ][p->op.params[2].value] =
		g_reg[p->champ][p->op.params[0].value] +
		g_reg[p->champ][p->op.params[0].value];
	if (g_reg[p->champ][p->op.params[2].value] == 0)
		g_carry = 1;
	vm_op_inc(vm, p);
}

void	vm_op_or(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}

void	vm_op_xor(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}
