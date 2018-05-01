/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 08:27:57 by fpetras           #+#    #+#             */
/*   Updated: 2018/05/01 21:32:34 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_op_inc(t_vm *vm, t_process *p)
{
	(void)vm;
	if (p->op.opcode != 0)
		p->pc = p->pc_next;
	else
		p->pc++;
	if (p->pc + p->offset >= MEM_SIZE)
		p->pc = p->offset * -1;
}

void	vm_op_live(t_vm *vm, t_process *p)
{
	(void)vm;
	p->live_nbr++;
	if (p->op.params[0].value == (p->champ * -1))
	{
		vm->champ[p->champ].live_nbr++;
		vm->last_live_champ = p->champ;
	}
	vm_op_inc(vm, p);
}

void	vm_op_ld(t_vm *vm, t_process *p)
{
	int		param0;

	(void)vm;
	if (p->op.params[1].value < 1 || p->op.params[1].value > 16)
	{
		vm_op_inc(vm, p);
		return ;
	}
	param0 = (p->op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[(p->offset + p->pc +
			(p->op.params[0].value % IDX_MOD)) % MEM_SIZE], 4)
		: p->op.params[0].value;
	g_reg[p->champ][p->op.params[1].value] = param0;
	if (param0 == 0)
		g_carry = 1;
	else
		g_carry = 0;
	vm_op_inc(vm, p);
}

void	vm_op_st(t_vm *vm, t_process *p)
{
	short	param1;
	char	*temp;

	(void)vm;
	if (p->op.params[0].value < 1 || p->op.params[0].value > 16 ||
		((p->op.params[1].type == REG_CODE) && (p->op.params[1].value < 1
			|| p->op.params[1].value > 16)))
	{
		vm_op_inc(vm, p);
		return ;
	}
	if (p->op.params[1].type == REG_CODE)
		g_reg[p->champ][p->op.params[1].value] =
			g_reg[p->champ][p->op.params[0].value];
	else
	{
		param1 = (p->offset + p->pc +
			((short)p->op.params[1].value % IDX_MOD)) % MEM_SIZE;
		(param1 < 0) ? param1 += MEM_SIZE : 0;
		temp = vm_to_big_endian(g_reg[p->champ][p->op.params[0].value], 4);
		vm_st_mem(param1, temp, p->champ, 4);
		free(temp);
	}
	vm_op_inc(vm, p);
}

void	vm_op_add(t_vm *vm, t_process *p)
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
		g_reg[p->champ][p->op.params[0].value] +
		g_reg[p->champ][p->op.params[1].value];
	if (g_reg[p->champ][p->op.params[2].value] == 0)
		g_carry = 1;
	else
		g_carry = 0;
	vm_op_inc(vm, p);
}
