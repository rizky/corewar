/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_print_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:51:02 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/27 15:01:44 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_lld_print(t_process p)
{
	int		param0;

	if (p.op.params[1].value < 1 || p.op.params[1].value > 16)
		return ;
	param0 = (p.op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[(p.offset + p.pc + p.op.params[0].value)
			% MEM_SIZE], 2)
		: p.op.params[0].value;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	(p.op.params[0].type == IND_CODE) ?
	ft_printf(" %hd", param0) : ft_printf(" %d", param0);
	ft_printf(" r%d", p.op.params[1].value);
	ft_printf("\n");
}

void
	vm_lldi_print2(t_process p, int param0, int param1)
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
		(p.offset + p.pc + ((short)param0 + (short)param1)));
	else if (p.op.params[0].type == DIR_CODE)
		ft_printf("       | -> load from %hd + %d = %d (with pc and mod %d)",
		param0, param1, (short)param0 + param1,
		(p.offset + p.pc + ((short)param0 + param1)));
	else if (p.op.params[1].type == DIR_CODE)
		ft_printf("       | -> load from %d + %hd = %d (with pc and mod %d)",
		param0, param1, param0 + (short)param1,
		(p.offset + p.pc + (param0 + (short)param1)));
	else
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)",
		param0, param1, param0 + param1,
		(p.offset + p.pc + (param0 + param1)));
	ft_printf("\n");
}

void
	vm_lldi_print(t_process p)
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
		vm_binary_toint(&g_memory[(p.offset + p.pc + p.op.params[0].value)], 4)
		: param0;
	vm_lldi_print2(p, param0, param1);
}

void
	vm_lfork_print(t_process p)
{
	ft_printf("P %4d | ", p.champ + 1);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" %hd (%hd)", p.op.params[0].value, p.pc + p.op.params[0].value);
	ft_printf("\n");
}

void
	vm_aff_print(t_process p)
{
	ft_printfln("Aff: %c", g_reg[p.champ][p.op.params[0].value]);
}
