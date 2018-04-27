/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_print_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:51:02 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/27 04:19:02 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_fork_print(t_process p)
{
	int i;

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
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" %d", param0);
	ft_printf(" r%d", p.op.params[1].value);
	ft_printf("\n");
}

void
	vm_st_print(t_process p)
{
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" r%d", p.op.params[0].value);
	ft_printf(" %d", p.op.params[1].value);
	ft_printf("\n");
}
