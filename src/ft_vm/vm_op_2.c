/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 08:29:15 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/27 17:16:41 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_op_sub(t_vm *vm, t_process *p)
{
	(void)vm;
	if (p->op.params[0].value < 1 ||
		p->op.params[0].value > 16 ||
		p->op.params[1].value < 1 ||
		p->op.params[1].value > 16 ||
		p->op.params[2].value < 1 ||
		p->op.params[2].value > 16)
	{
		vm_op_inc(vm, p);
		return ;
	}
	g_reg[p->champ][p->op.params[2].value] =
		g_reg[p->champ][p->op.params[0].value] -
		g_reg[p->champ][p->op.params[1].value];
	if (g_reg[p->champ][p->op.params[2].value] == 0)
		g_carry = 1;
	else
		g_carry = 0;
	vm_op_inc(vm, p);
}

void	vm_op_and(t_vm *vm, t_process *p)
{
	int		param0;
	int		param1;

	(void)vm;
	if (p->op.params[2].value < 1 || p->op.params[2].value > 16 ||
	((p->op.params[1].type == REG_CODE) && (p->op.params[1].value < 1 ||
	p->op.params[1].value > 16)) || ((p->op.params[0].type == REG_CODE) &&
	(p->op.params[0].value < 1 || p->op.params[0].value > 16)))
	{
		vm_op_inc(vm, p);
		return ;
	}
	param0 = (p->op.params[0].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[0].value] : p->op.params[0].value;
	param1 = (p->op.params[1].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[1].value] : p->op.params[1].value;
	param0 = (p->op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p->offset + p->pc +
		p->op.params[0].value % IDX_MOD], 4) : param0;
	param1 = (p->op.params[1].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p->offset + p->pc +
		p->op.params[1].value % IDX_MOD], 4) : param1;
	g_reg[p->champ][p->op.params[2].value] = param0 & param1;
	g_carry = (g_reg[p->champ][p->op.params[2].value] == 0) ? 1 : 0;
	vm_op_inc(vm, p);
}

void	vm_op_or(t_vm *vm, t_process *p)
{
	int		param0;
	int		param1;

	(void)vm;
	if (p->op.params[2].value < 1 || p->op.params[2].value > 16 ||
	((p->op.params[1].type == REG_CODE) && (p->op.params[1].value < 1 ||
	p->op.params[1].value > 16)) || ((p->op.params[0].type == REG_CODE) &&
	(p->op.params[0].value < 1 || p->op.params[0].value > 16)))
	{
		vm_op_inc(vm, p);
		return ;
	}
	param0 = (p->op.params[0].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[0].value] : p->op.params[0].value;
	param1 = (p->op.params[1].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[1].value] : p->op.params[1].value;
	param0 = (p->op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p->offset + p->pc +
		p->op.params[0].value % IDX_MOD], 4) : param0;
	param1 = (p->op.params[1].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p->offset + p->pc +
		p->op.params[1].value % IDX_MOD], 4) : param1;
	g_reg[p->champ][p->op.params[2].value] = param0 | param1;
	g_carry = (g_reg[p->champ][p->op.params[2].value] == 0) ? 1 : 0;
	vm_op_inc(vm, p);
}

void	vm_op_xor(t_vm *vm, t_process *p)
{
	int		param0;
	int		param1;

	(void)vm;
	if (p->op.params[2].value < 1 || p->op.params[2].value > 16 ||
	((p->op.params[1].type == REG_CODE) && (p->op.params[1].value < 1 ||
	p->op.params[1].value > 16)) || ((p->op.params[0].type == REG_CODE) &&
	(p->op.params[0].value < 1 || p->op.params[0].value > 16)))
	{
		vm_op_inc(vm, p);
		return ;
	}
	param0 = (p->op.params[0].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[0].value] : p->op.params[0].value;
	param1 = (p->op.params[1].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[1].value] : p->op.params[1].value;
	param0 = (p->op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p->offset + p->pc +
		p->op.params[0].value % IDX_MOD], 4) : param0;
	param1 = (p->op.params[1].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p->offset + p->pc +
		p->op.params[1].value % IDX_MOD], 4) : param1;
	g_reg[p->champ][p->op.params[2].value] = param0 ^ param1;
	g_carry = (g_reg[p->champ][p->op.params[2].value] == 0) ? 1 : 0;
	vm_op_inc(vm, p);
}
