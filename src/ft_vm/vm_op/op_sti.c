/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:56:40 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/02 18:59:38 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_op_sti(t_vm *vm, t_process *p)
{
	int			param1;
	int			param2;
	int			cursor;
	char		*temp;

	(void)vm;
	if (p->op.params[0].value < 1 || p->op.params[0].value > 16 ||
		((p->op.params[1].type == REG_CODE) &&
			(p->op.params[1].value < 1 || p->op.params[1].value > 16)) ||
		((p->op.params[2].type == REG_CODE) &&
			(p->op.params[2].value < 1 || p->op.params[2].value > 16)))
	{
		vm_op_inc(vm, p);
		return ;
	}
	param1 = ft_init_param(p, 1);
	param2 = (p->op.params[2].type == REG_CODE) ?
		p->reg[p->op.params[2].value] : p->op.params[2].value;
	cursor = ft_cursor(p, param1, param2, 1) % MEM_SIZE;
	if (cursor < 0)
		cursor += MEM_SIZE;
	temp = vm_to_big_endian(p->reg[p->op.params[0].value], 4);
	vm_st_mem(cursor, temp, p->champ, 4);
	free(temp);
	vm_op_inc(vm, p);
}

void
	vm_sti_print2(t_process p, int param1, int param2)
{
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" r%d", p.op.params[0].value);
	(p.op.params[1].type == DIR_CODE) ?
	ft_printf(" %hd", param1) : ft_printf(" %d", param1);
	(p.op.params[2].type == DIR_CODE) ?
	ft_printf(" %hd\n", param2) : ft_printf(" %d\n", param2);
	if (p.op.params[1].type == DIR_CODE && p.op.params[2].type == DIR_CODE)
		ft_printf("       | -> store to %hd + %hd = %d (with pc and mod %d)",
		param1, param2, (short)param1 + (short)param2,
		p.offset + p.pc + ((short)param1 + (short)param2) % IDX_MOD);
	else if (p.op.params[1].type == DIR_CODE)
		ft_printf("       | -> store to %hd + %d = %d (with pc and mod %d)",
		param1, param2, (short)param1 + param2,
		p.offset + p.pc + ((short)param1 + param2) % IDX_MOD);
	else if (p.op.params[2].type == DIR_CODE)
		ft_printf("       | -> store to %d + %hd = %d (with pc and mod %d)",
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
	param1 = (p.op.params[1].type == REG_CODE) ?
		p.reg[p.op.params[1].value] : p.op.params[1].value;
	param2 = (p.op.params[2].type == REG_CODE) ?
		p.reg[p.op.params[2].value] : p.op.params[2].value;
	param1 = (p.op.params[1].type == IND_CODE) ?
		vm_ld_mem((p.offset + p.pc +
			(p.op.params[1].value % IDX_MOD)) % MEM_SIZE, 4) : param1;
	vm_sti_print2(p, param1, param2);
}
