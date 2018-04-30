/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_print_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:51:02 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/27 16:26:18 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_fork_print(t_process p)
{
	int value;

	ft_printf("P %4d | ", p.champ + 1);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	value = p.pc + p.offset + p.op.params[0].value;
	if (value > MEM_SIZE)
		value = value % MEM_SIZE;
	ft_printf(" %hd (%hd)", p.op.params[0].value, p.pc + p.offset + p.op.params[0].value);
	ft_printf("\n");
}

void
	vm_ld_print(t_process p)
{
	int param0;

	if (p.op.params[1].value < 1 || p.op.params[1].value > 16)
		return ;
	param0 = (p.op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[(p.offset + p.pc + p.op.params[0].value) % IDX_MOD], 4)
		: p.op.params[0].value;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" %d", param0);
	ft_printf(" r%d", p.op.params[1].value);
	ft_printf("\n");
}

void
	vm_ldi_print(t_process p)
{
	int param0;
	int	param1;
	// int cursor;

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
		vm_binary_toint(&g_memory[(p.offset + p.pc + p.op.params[0].value) % IDX_MOD], 4)
		: param0;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	(p.op.params[0].type == DIR_CODE) ?
	ft_printf(" %hd", param0) : ft_printf(" %d", param0);
	(p.op.params[1].type == DIR_CODE) ?
	ft_printf(" %hd", param1) : ft_printf(" %d", param1);
	ft_printf(" r%d", p.op.params[2].value);
	ft_printf("\n");
	if (p.op.params[0].type == DIR_CODE && p.op.params[1].type == DIR_CODE)
	{
		ft_printf("       | -> load from %hd + %hd = %d (with pc and mod %d)",
		param0, param1, (short)param0 + (short)param1,
		(p.offset + p.pc + (short)param0 + (short)param1) % IDX_MOD);
	}
	else if (p.op.params[0].type == DIR_CODE)
	{
		ft_printf("       | -> load from %hd + %d = %d (with pc and mod %d)",
		param0, param1, (short)param0 + param1,
		(p.offset + p.pc + (short)param0 + param1) % IDX_MOD);
	}
	else if (p.op.params[1].type == DIR_CODE)
	{
		ft_printf("       | -> load from %d + %hd = %d (with pc and mod %d)",
		param0, param1, param0 + (short)param1,
		(p.offset + p.pc + param0 + (short)param1) % IDX_MOD);
	}
	else
	{
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)",
		param0, param1, param0 + param1,
		(p.offset + p.pc + param0 + param1) % IDX_MOD);
	}
	
	ft_printf("\n");
}

void
	vm_st_print(t_process p)
{
	if (p.op.params[0].value < 1 || p.op.params[0].value > 16 ||
		((p.op.params[1].type == REG_CODE) &&
			(p.op.params[1].value < 1 || p.op.params[1].value > 16)))
		return ;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" r%d", p.op.params[0].value);
	ft_printf(" %hd", p.op.params[1].value);
	ft_printf("\n");
}

void
	vm_add_print(t_process p)
{
	if (p.op.params[0].value < 1 ||
		p.op.params[0].value > 16 ||
		p.op.params[1].value < 1 ||
		p.op.params[1].value > 16 ||
		p.op.params[2].value < 1 ||
		p.op.params[2].value > 16)
		return ;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" r%d", p.op.params[0].value);
	ft_printf(" r%d", p.op.params[1].value);
	ft_printf(" r%d", p.op.params[2].value);
	ft_printf("\n");
}
