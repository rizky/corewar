/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_print_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:51:02 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/27 15:02:02 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_fork_print(t_process p)
{
	int i;

	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	i = -1;
	ft_printf(" %hd (%hd)", p.op.params[0].value, p.op.params[0].value);
	ft_printf("\n");
}

void
	vm_ld_print(t_process p)
{
	int param0;

	param0 = (p.op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p.offset + p.pc + p.op.params[0].value], 4)
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

	param0 = (p.op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p.offset + p.pc + p.op.params[0].value], 4)
		: p.op.params[0].value;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" %d", param0);
	ft_printf(" %d", p.op.params[1].value);
	ft_printf(" r%d", p.op.params[2].value);
	ft_printf("\n");
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)",
		param0, p.op.params[1].value, param0 + p.op.params[1].value,
		(p.offset + p.pc + param0 + p.op.params[1].value) % IDX_MOD);
	ft_printf("\n");
}

void
	vm_st_print(t_process p)
{
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" r%d", p.op.params[0].value);
	ft_printf(" %d", p.op.params[1].value);
	ft_printf("\n");
}

void
	vm_add_print(t_process p)
{
	if (g_reg[p.champ][p.op.params[0].value] < 1 ||
		g_reg[p.champ][p.op.params[0].value] > 16 ||
		g_reg[p.champ][p.op.params[1].value] < 1 ||
		g_reg[p.champ][p.op.params[1].value] > 16 ||
		g_reg[p.champ][p.op.params[2].value] < 1 ||
		g_reg[p.champ][p.op.params[2].value] > 16)
		return ;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" r%d", p.op.params[0].value);
	ft_printf(" r%d", p.op.params[1].value);
	ft_printf(" r%d", p.op.params[2].value);
	ft_printf("\n");
}
