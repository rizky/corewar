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
	vm_and_print(t_process p)
{
	if (p.op.params[2].value < 1 || p.op.params[2].value > 16 ||
		((p.op.params[1].type == REG_CODE) &&
			(p.op.params[1].value < 1 || p.op.params[1].value > 16)) ||
		((p.op.params[0].type == REG_CODE) &&
			(p.op.params[0].value < 1 || p.op.params[0].value > 16)))
		return ;
	(void)p;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	if (p.op.params[0].type == REG_CODE)
		ft_printf(" %d", g_reg[p.champ][p.op.params[0].value]);
	else if (p.op.params[0].type == IND_CODE)
		ft_printf(" %d", vm_binary_toint(&g_memory[p.offset +
			p.pc + p.op.params[0].value % IDX_MOD], 4));
	else
		ft_printf(" %d", p.op.params[0].value);
	if (p.op.params[1].type == REG_CODE)
		ft_printf(" %d", g_reg[p.champ][p.op.params[1].value]);
	else if (p.op.params[1].type == IND_CODE)
		ft_printf(" %d", vm_binary_toint(&g_memory[p.offset + p.pc
			+ p.op.params[1].value % IDX_MOD], 4));
	else
		ft_printf(" %d", p.op.params[1].value);
	ft_printf(" r%d", p.op.params[2].value);
	ft_printf("\n");
}

void
	vm_or_print(t_process p)
{
	if (p.op.params[2].value < 1 || p.op.params[2].value > 16 ||
		((p.op.params[1].type == REG_CODE) &&
			(p.op.params[1].value < 1 || p.op.params[1].value > 16)) ||
		((p.op.params[0].type == REG_CODE) &&
			(p.op.params[0].value < 1 || p.op.params[0].value > 16)))
		return ;
	(void)p;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	if (p.op.params[0].type == REG_CODE)
		ft_printf(" %d", g_reg[p.champ][p.op.params[0].value]);
	else if (p.op.params[0].type == IND_CODE)
		ft_printf(" %d", vm_binary_toint(&g_memory[p.offset +
		p.pc + p.op.params[0].value % IDX_MOD], 4));
	else
		ft_printf(" %d", p.op.params[0].value);
	if (p.op.params[1].type == REG_CODE)
		ft_printf(" %d", g_reg[p.champ][p.op.params[1].value]);
	else if (p.op.params[1].type == IND_CODE)
		ft_printf(" %d", vm_binary_toint(&g_memory[p.offset +
		p.pc + p.op.params[1].value % IDX_MOD], 4));
	else
		ft_printf(" %d", p.op.params[1].value);
	ft_printf(" r%d", p.op.params[2].value);
	ft_printf("\n");
}

void
	vm_xor_print(t_process p)
{
	if (p.op.params[2].value < 1 || p.op.params[2].value > 16 ||
		((p.op.params[1].type == REG_CODE) &&
			(p.op.params[1].value < 1 || p.op.params[1].value > 16)) ||
		((p.op.params[0].type == REG_CODE) &&
			(p.op.params[0].value < 1 || p.op.params[0].value > 16)))
		return ;
	(void)p;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	if (p.op.params[0].type == REG_CODE)
		ft_printf(" %d", g_reg[p.champ][p.op.params[0].value]);
	else if (p.op.params[0].type == IND_CODE)
		ft_printf(" %d", vm_binary_toint(&g_memory[p.offset
		+ p.pc + p.op.params[0].value % IDX_MOD], 4));
	else
		ft_printf(" %d", p.op.params[0].value);
	if (p.op.params[1].type == REG_CODE)
		ft_printf(" %d", g_reg[p.champ][p.op.params[1].value]);
	else if (p.op.params[1].type == IND_CODE)
		ft_printf(" %d", vm_binary_toint(&g_memory[p.offset +
		p.pc + p.op.params[1].value % IDX_MOD], 4));
	else
		ft_printf(" %d", p.op.params[1].value);
	ft_printf(" r%d", p.op.params[2].value);
	ft_printf("\n");
}

void
	vm_zjmp_print(t_process p)
{
	short	value;

	(void)p;
	value = (p.op.params[0].value + p.offset + p.pc);
	if (value > MEM_SIZE)
		value = (p.op.params[0].value + p.offset + p.pc) % MEM_SIZE;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" %d", value - (p.offset + p.pc));
	if (!g_carry)
		ft_printf(" FAILED");
	else
		ft_printf(" OK");
	ft_printf("\n");
}
