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
	vm_op_print(t_process p)
{
	int i;

	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	i = -1;
	while (++i < p.op.param_c)
		if (p.op.params[i].type == REG_CODE)
			if (i > 0)
				ft_printf(" %hd", g_reg[p.champ][p.op.params[i].value]);
			else
				ft_printf(" r%d", p.op.params[i].value);
		else
			ft_printf(" %hd", p.op.params[i].value);
	ft_printf("\n");
}

void
	vm_and_print(t_process p)
{
	int i;

	(void)p;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" %d", g_reg[p.champ][p.op.params[0].value]);
	i = 0;
	while (++i < p.op.param_c)
		if (p.op.params[i].type == REG_CODE)
			ft_printf(" r%d", p.op.params[i].value);
		else
			ft_printf(" %d", p.op.params[i].value);
	ft_printf("\n");
}

void
	vm_live_print(t_process p)
{
	ft_printf("P %4d | ", p.champ + 1);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" %d", vm_binary_toint(&g_memory[p.pc + 1], 4));
	ft_printf("\n");
}

void
	vm_zjmp_print(t_process p)
{
	int	value;

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

void
	vm_sti_print(t_process p)
{
	int param1;
	int param2;

	param1 = (p.op.params[1].type == REG_CODE) ?
		g_reg[p.champ][p.op.params[1].value] : p.op.params[1].value;
	param1 = (p.op.params[1].type == IND_CODE) ?
		vm_binary_toint(&g_memory[p.offset + p.pc + p.op.params[1].value], 4)
		: param1;
	param2 = (p.op.params[2].type == REG_CODE) ?
		g_reg[p.champ][p.op.params[2].value] : p.op.params[2].value;
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printfln(" r%d %d %hd", p.op.params[0].value, param1, param2);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)",
		param1, param2, param1 + param2,
		(p.offset + p.pc + param1 + param2) % IDX_MOD);
	ft_printf("\n");
}

void
    vm_lfork_print(t_process p)
{
    ft_printf("P %4d | ", p.champ + 1);
    ft_printf("%s", g_op_dict[p.op.opcode].name);
    ft_printf(" %hd (%hd)", p.op.params[0].value, p.pc + p.op.params[0].value);
    ft_printf("\n");
}
