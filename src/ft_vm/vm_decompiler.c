/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_decompiler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 15:59:39 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/04 01:44:13 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int			vm_checker_oc(t_op op)
{
	int param[3];
	int i;

	if (!g_op_dict[op.opcode].is_oc)
		return (0);
	param[0] = (op.oc & 192) >> 6;
	param[1] = (op.oc & 48) >> 4;
	param[2] = (op.oc & 12) >> 2;
	i = 0;
	while (i != 3)
	{
		if (param[i] == IND_CODE && !(g_op_dict[op.opcode].p_type[i] >= T_IND))
			return (-1);
		if (param[i] == DIR_CODE && !(g_op_dict[op.opcode].p_type[i] & T_DIR))
			return (-1);
		if (param[i] == REG_CODE && !(g_op_dict[op.opcode].p_type[i] & T_REG))
			return (-1);
		if (param[i] == 0 && g_op_dict[op.opcode].p_type[i])
			return (-1);
		i++;
	}
	return (0);
}

void		vm_decompiler_param(t_process *p, t_op *op)
{
	int		i;

	i = 0;
	op->size += g_op_dict[op->opcode].is_oc ? 2 : 1;
	op->oc = (g_op_dict[op->opcode].is_oc) ?
		g_memory[p->offset + p->pc + 1] :
		g_op_dict[op->opcode].p_type[0];
	op->param_c = g_op_dict[op->opcode].param_c;
	while (i < op->param_c)
	{
		op->params[i].type = (g_op_dict[op->opcode].is_oc) ?
		(op->oc & (0xC0 >> (i * 2))) >> ((3 - i) * 2) : op->oc;
		(op->params[i].type == REG_CODE) ? op->params[i].size = 1 : 0;
		(op->params[i].type == IND_CODE) ? op->params[i].size = 2 : 0;
		(op->params[i].type == DIR_CODE) ? op->params[i].size =
			g_op_dict[op->opcode].d_size : 0;
		op->params[i].value =
		vm_ld_mem(p->offset + p->pc + op->size,
			op->params[i].size);
		op->size += op->params[i].size;
		i++;
	}
}

static int	vm_decompiler_op(t_vm *vm, t_process *p, t_op *op)
{
	const int cursor = g_memory[p->offset + p->pc];

	(void)vm;
	if (cursor < 0x01 || cursor > 0x10)
		return (-1);
	op->opcode = cursor;
	p->cycles = g_cycles - 1 + g_op_dict[op->opcode].cycles;
	return (0);
}

void		vm_decompiler(t_vm *vm)
{
	int			i;
	t_op		op;
	t_process	*p;

	i = -1;
	while (++i < (int)(vm->processes.size))
	{
		ft_bzero(&op, sizeof(t_op));
		p = &(((t_process*)vm->processes.data)[i]);
		if (p->op.opcode == 0)
		{
			p->cycles = g_cycles;
			vm_decompiler_op(vm,
				&(((t_process*)vm->processes.data)[i]),
				&op);
			p->op = op;
		}
	}
}
