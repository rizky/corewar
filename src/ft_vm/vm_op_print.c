/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:51:02 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/24 16:17:12 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_op_print(t_op op, t_process p)
{
	int i;

	(void)p;
	ft_printf("%s", g_op_dict[op.opcode].name);
	i = -1;
	while (++i < op.param_c)
		if (op.params[i].type == REG_CODE)
			ft_printf(" r%d", op.params[i].value);
		else
			ft_printf(" %d", op.params[i].value);
	ft_printf("\n");
}

void
	vm_and_print(t_op op, t_process p)
{
	int i;

	(void)p;
	ft_printf("%s", g_op_dict[op.opcode].name);
	ft_printf(" %d", g_reg[op.params[0].value]);
	i = 0;
	while (++i < op.param_c)
		if (op.params[i].type == REG_CODE)
			ft_printf(" r%d", op.params[i].value);
		else
			ft_printf(" %d", op.params[i].value);
	ft_printf("\n");
}

void
	vm_live_print(t_op op, t_process p)
{
	ft_printf("%s", g_op_dict[op.opcode].name);
	ft_printf(" %d", vm_binary_toint(&g_memory[p.pc_next], 4));
	ft_printf("\n");
}

void
	vm_zjump_print(t_op op, t_process p)
{
	int	value;

	(void)p;
	value = 0;
	if ((op.params[0].value + p.offset + p.pc) > MEM_SIZE)
		value = (op.params[0].value + p.offset + p.pc) % MEM_SIZE;
	ft_printf("%s", g_op_dict[op.opcode].name);
	ft_printf(" %d", value - (p.offset + p.pc));
	if (!g_carrier)
		ft_printf(" FAILED");
	ft_printf("\n");
}

void
	vm_sti_print(t_op op, t_process p)
{
	int param1;
	int param2;

	(void)p;
	param1 = (op.params[1].type == REG_CODE) ?
		g_reg[op.params[1].value] : op.params[1].value;
	param2 = (op.params[2].type == REG_CODE) ?
		g_reg[op.params[2].value] : op.params[2].value;
	vm_op_print(op, p);
	ft_printf("      | -> store to %d + %d = %d (with pc and mod %d)",
		param1, param2, param1 + param2, p.pc + param1 + param2);
	ft_printf("\n");
}

void
	vm_print_v_4(t_vm vm)
{
	int		i;
	int		j;
	t_op	op;

	i = vm.champ_size - 1;
	while (i >= 0)
	{
		j = -1;
		while (++j < (int)(vm.champ[i].processes->size))
		{
			op = (((t_process*)vm.champ[i].processes->data)[j]).op;
			if (op.opcode != 0)
			{
				ft_printf("P %3d | ", j + 1);
				(((void (*)())g_op_dict[op.opcode].opprint)(op,
					((t_process*)vm.champ[i].processes->data)[j]));
			}
		}
		i--;
	}
}
