/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_print_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 15:13:56 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/27 17:23:23 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_sti_print2(t_process p, int param1, int param2)
{
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printfln(" r%d ", p.op.params[0].value);
	(p.op.params[0].type == DIR_CODE) ?
	ft_printf(" %hd", param1) : ft_printf(" %d", param1);
	(p.op.params[1].type == DIR_CODE) ?
	ft_printf(" %hd\n", param2) : ft_printf(" %d", param2);
	if (p.op.params[1].type == DIR_CODE && p.op.params[2].type == DIR_CODE)
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)",
		param1, param2, (short)param1 + (short)param2,
		p.offset + p.pc + ((short)param1 + (short)param2) % IDX_MOD);
	else if (p.op.params[1].type == DIR_CODE)
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)",
		param1, param2, (short)param1 + param2,
		p.offset + p.pc + ((short)param1 + param2) % IDX_MOD);
	else if (p.op.params[2].type == DIR_CODE)
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)",
		param1, param2, param1 + (short)param2,
		p.offset + p.pc + (param1 + (short)param2) % IDX_MOD);
	else
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)",
		param1, param2, param1 + param2,
		p.offset + p.pc + (param1 + param2) % IDX_MOD);
	ft_printf("\n");
}

void
	vm_sti_print(t_process p)
{
	int param1;
	int param2;

	if (p.op.params[0].value < 1 || p.op.params[0].value > 16 ||
		((p.op.params[1].type == REG_CODE) &&
			(p.op.params[1].value < 1 || p.op.params[1].value > 16)) ||
		((p.op.params[2].type == REG_CODE) &&
			(p.op.params[2].value < 1 || p.op.params[2].value > 16)))
		return ;
	param1 = (p.op.params[0].type == REG_CODE) ?
		g_reg[p.champ][p.op.params[0].value] : p.op.params[0].value;
	param2 = (p.op.params[1].type == REG_CODE) ?
		g_reg[p.champ][p.op.params[1].value] : p.op.params[1].value;
	param1 = (p.op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p.offset + p.pc +
			p.op.params[0].value % IDX_MOD], 4) : param1;
	vm_sti_print2(p, param1, param2);
}

void
	vm_ldi_print2(t_process p, int param0, int param1)
{
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	(p.op.params[0].type == DIR_CODE) ?
	ft_printf(" %hd", param0) : ft_printf(" %d", param0);
	(p.op.params[1].type == DIR_CODE) ?
	ft_printf(" %hd", param1) : ft_printf(" %d", param1);
	ft_printf(" r%d", p.op.params[2].value);
	ft_printf("\n");
	if (p.op.params[0].type == DIR_CODE && p.op.params[1].type == DIR_CODE)
		ft_printf("       | -> load from %hd + %hd = %d (with pc and mod %d)",
		param0, param1, (short)param0 + (short)param1,
		p.offset + p.pc + ((short)param0 + (short)param1) % IDX_MOD);
	else if (p.op.params[0].type == DIR_CODE)
		ft_printf("       | -> load from %hd + %d = %d (with pc and mod %d)",
		param0, param1, (short)param0 + param1,
		p.offset + p.pc + ((short)param0 + param1) % IDX_MOD);
	else if (p.op.params[1].type == DIR_CODE)
		ft_printf("       | -> load from %d + %hd = %d (with pc and mod %d)",
		param0, param1, param0 + (short)param1,
		p.offset + p.pc + (param0 + (short)param1) % IDX_MOD);
	else
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)",
		param0, param1, param0 + param1,
		p.offset + p.pc + (param0 + param1) % IDX_MOD);
	ft_printf("\n");
}

void
	vm_ldi_print(t_process p)
{
	int param0;
	int	param1;

	if (p.op.params[2].value < 1 || p.op.params[2].value > 16 ||
		((p.op.params[1].type == REG_CODE) &&
			(p.op.params[1].value < 1 || p.op.params[1].value > 16)) ||
		((p.op.params[0].type == REG_CODE) &&
			(p.op.params[0].value < 1 || p.op.params[0].value > 16)))
		return ;
	param0 = (p.op.params[0].type == REG_CODE) ?
		g_reg[p.champ][p.op.params[0].value] : p.op.params[0].value;
	param1 = (p.op.params[1].type == REG_CODE) ?
		g_reg[p.champ][p.op.params[1].value] : p.op.params[1].value;
	param0 = (p.op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p.offset + p.pc
		+ p.op.params[0].value % IDX_MOD], 4) : param0;
	vm_ldi_print2(p, param0, param1);
}

void
	vm_fork_print(t_process p)
{
	int value;

	ft_printf("P %4d | ", p.champ + 1);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	value = p.pc + p.offset + p.op.params[0].value;
	if (value > MEM_SIZE)
		value = value % MEM_SIZE;
	ft_printf(" %hd (%hd)", p.op.params[0].value,
		p.pc + p.offset + p.op.params[0].value);
	ft_printf("\n");
}
