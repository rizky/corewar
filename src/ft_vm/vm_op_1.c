/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 08:27:57 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/27 16:26:10 by rnugroho         ###   ########.fr       */
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
	int		param0;

	(void)vm;
	param0 = (p->op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p->offset + p->pc + p->op.params[0].value], 4)
		: p->op.params[0].value;
	g_reg[p->champ][p->op.params[1].value] = param0;
	if (param0 == 0)
		g_carry = 1;
	vm_op_inc(vm, p);
}

void	vm_op_st(t_vm *vm, t_process *p)
{
	int		param1;
	char	*temp;

	(void)vm;
	if (p->op.params[0].value < 1 ||
		p->op.params[0].value > 16)
		vm_op_inc(vm, p);
	param1 = (p->op.params[1].type == REG_CODE) ?
		g_reg[p->champ][p->op.params[1].value] : p->op.params[1].value;
	temp = vm_to_big_endian(g_reg[p->champ][p->op.params[0].value], 4);
	ft_memcpy(&g_memory[(p->offset + p->pc + param1) % IDX_MOD],
		temp, 4);
	vm_memmark(&g_memory_mark[(p->offset + p->pc + param1) % IDX_MOD],
		p->champ + 1, 4);
	free(temp);
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
		vm_op_inc(vm, p);
	g_reg[p->champ][p->op.params[2].value] =
		g_reg[p->champ][p->op.params[0].value] +
		g_reg[p->champ][p->op.params[1].value];
	if (g_reg[p->champ][p->op.params[2].value] == 0)
		g_carry = 1;
	vm_op_inc(vm, p);
}
