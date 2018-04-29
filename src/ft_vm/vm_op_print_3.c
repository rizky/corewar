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
	vm_sub_print(t_process p)
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

void
	vm_aff_print(t_process p)
{
	ft_printfln("Aff: %c", g_reg[p.champ][p.op.params[0].value]);
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
	(p.op.params[0].type == REG_CODE) ? ft_printf(" %d", g_reg[p.champ][p.op.params[0].value]) :
	(p.op.params[0].type == IND_CODE) ?
		ft_printf(" %d", vm_binary_toint(&g_memory[(p.offset + p.pc + p.op.params[0].value) % IDX_MOD], 4))
		: ft_printf(" %d", p.op.params[0].value);
	(p.op.params[1].type == REG_CODE) ? ft_printf(" %d", g_reg[p.champ][p.op.params[1].value]) :
	(p.op.params[1].type == IND_CODE) ?
		ft_printf(" %d", vm_binary_toint(&g_memory[(p.offset + p.pc + p.op.params[1].value) % IDX_MOD], 4))
		: ft_printf(" %d", p.op.params[1].value);
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
	(p.op.params[0].type == REG_CODE) ? ft_printf(" %d", g_reg[p.champ][p.op.params[0].value]) :
	(p.op.params[0].type == IND_CODE) ?
		ft_printf(" %d", vm_binary_toint(&g_memory[(p.offset + p.pc + p.op.params[0].value) % IDX_MOD], 4))
		: ft_printf(" %d", p.op.params[0].value);
	(p.op.params[1].type == REG_CODE) ? ft_printf(" %d", g_reg[p.champ][p.op.params[1].value]) :
	(p.op.params[1].type == IND_CODE) ?
		ft_printf(" %d", vm_binary_toint(&g_memory[(p.offset + p.pc + p.op.params[1].value) % IDX_MOD], 4))
		: ft_printf(" %d", p.op.params[1].value);
	ft_printf(" r%d", p.op.params[2].value);
	ft_printf("\n");
}