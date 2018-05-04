/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:59:23 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/03 11:26:02 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

static int	ft_init_param_long(t_process *p, int i)
{
	int			result;

	result = (p->op.params[i].type == REG_CODE) ?
		p->reg[p->op.params[i].value] : p->op.params[i].value;
	result = (p->op.params[i].type == IND_CODE) ?
		vm_ld_mem(p->offset + p->pc + p->op.params[i].value, 4)
		: result;
	return (result);
}

static int	ft_cursor_long(t_process *p, int param1, int param2, int i)
{
	int cursor;

	if (p->op.params[i].type == DIR_CODE && p->op.params[i + 1].type
		== DIR_CODE)
		cursor = p->offset + p->pc + ((short)param1 + (short)param2);
	else if (p->op.params[i].type == DIR_CODE)
		cursor = p->offset + p->pc + ((short)param1 + param2);
	else if (p->op.params[i + 1].type == DIR_CODE)
		cursor = p->offset + p->pc + (param1 + (short)param2);
	else
		cursor = p->offset + p->pc + (param1 + param2);
	return (cursor);
}

void		vm_op_lldi(t_vm *vm, t_process *p)
{
	int		param0;
	int		param1;
	int		cursor;

	(void)vm;
	if (p->op.params[2].value < 1 || p->op.params[2].value > 16 ||
		((p->op.params[1].type == REG_CODE) &&
			(p->op.params[1].value < 1 || p->op.params[1].value > 16)) ||
		((p->op.params[0].type == REG_CODE) &&
			(p->op.params[0].value < 1 || p->op.params[0].value > 16)))
	{
		vm_op_inc(vm, p);
		return ;
	}
	param0 = ft_init_param_long(p, 0);
	param1 = (p->op.params[1].type == REG_CODE) ?
		p->reg[p->op.params[1].value] : p->op.params[1].value;
	cursor = ft_cursor_long(p, param0, param1, 0) % MEM_SIZE;
	(cursor < 0) ? cursor += MEM_SIZE : 0;
	p->reg[p->op.params[2].value] = vm_ld_mem(cursor, 4);
	p->carry = (p->reg[p->op.params[2].value] == 0) ? 1 : 0;
	vm_op_inc(vm, p);
}

static void	vm_lldi_print2(t_process p, int param0, int param1)
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
		ft_printf("       | -> load from %hd + %hd = %d (with pc %d)",
		param0, param1, (short)param0 + (short)param1,
		(p.offset + p.pc + ((short)param0 + (short)param1)));
	else if (p.op.params[0].type == DIR_CODE)
		ft_printf("       | -> load from %hd + %d = %d (with pc %d)",
		param0, param1, (short)param0 + param1,
		(p.offset + p.pc + ((short)param0 + param1)));
	else if (p.op.params[1].type == DIR_CODE)
		ft_printf("       | -> load from %d + %hd = %d (with pc %d)",
		param0, param1, param0 + (short)param1,
		(p.offset + p.pc + (param0 + (short)param1)));
	else
		ft_printf("       | -> load from %d + %d = %d (with pc %d)",
		param0, param1, param0 + param1,
		(p.offset + p.pc + (param0 + param1)));
	ft_printf("\n");
}

void		vm_lldi_print(t_process p)
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
		p.reg[p.op.params[0].value] : p.op.params[0].value;
	param1 = (p.op.params[1].type == REG_CODE) ?
		p.reg[p.op.params[1].value] : p.op.params[1].value;
	param0 = (p.op.params[0].type == IND_CODE) ?
		vm_ld_mem((p.offset + p.pc + p.op.params[0].value), 4)
		: param0;
	vm_lldi_print2(p, param0, param1);
}
