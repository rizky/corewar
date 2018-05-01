/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_print_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:51:02 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/01 19:45:16 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_live_print(t_process p)
{
	ft_printf("P %4d | ", p.champ + 1);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" %d", p.op.params[0].value);
	ft_printf("\n");
}

void
	vm_ld_print(t_process p)
{
	int param0;

	if (p.op.params[1].value < 1 || p.op.params[1].value > 16)
		return ;
	param0 = (p.op.params[0].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p.offset + p.pc +
		p.op.params[0].value % IDX_MOD], 4) : p.op.params[0].value;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" %d", param0);
	ft_printf(" r%d", p.op.params[1].value);
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
