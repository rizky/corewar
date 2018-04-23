/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:23:54 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/23 20:08:17 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int
	vm_decompiler_param(t_process *p, t_op *op, int c)
{
	int		i;

	i = 0;
	while (i < g_op_dict[op->opcode].param_c)
	{
		op->params[i].type = (g_op_dict[op->opcode].is_oc) ?
			(op->oc & (0xC0 >> (i * 2))) >> ((3 - i) * 2) : op->oc;
		if ((op->params[i].type & g_op_dict[op->opcode].p_type[i]) ==
			op->params[i].type || !g_op_dict[op->opcode].is_oc)
		{
			(op->params[i].type == T_REG) ? op->params[i].size = 1 : 0;
			(op->params[i].type == T_IND) ? op->params[i].size = 2 : 0;
			(op->params[i].type == T_DIR) ? op->params[i].size =
				g_op_dict[op->opcode].d_size : 0;
			op->params[i].value =
			vm_binary_toint(&g_memory[p->offset + p->pc + c + i],
				op->params[i].size);
			op->size += op->params[i].size;
		}
		else
			return (-1);
		i++;
	}
	return (0);
}

int
	vm_decompiler_op(t_vm *vm, t_process *p, t_op *op)
{
	int		c;

	(void)vm;
	c = 1;
	op->opcode = g_memory[p->offset + p->pc];
	if (op->opcode < 0x01 || op->opcode > 0x10)
		return (-1);
	if (g_op_dict[op->opcode].is_oc)
		op->oc = g_memory[p->offset + p->pc + c];
	else
		op->oc = g_op_dict[op->opcode].p_type[0];
	c++;
	if (vm_decompiler_param(p, op, c) == -1)
		return (-1);
	op->size += g_op_dict[op->opcode].is_oc ? 2 : 1;
	p->pc += op->size;
	return (0);
}

void
	vm_executor_process(t_vm *vm, t_process *p)
{
	t_op op;

	ft_bzero(&op, sizeof(t_op));
	if (vm_decompiler_op(vm, p, &op) == -1)
		vm_op_inc(vm, p, NULL);
}

void
	vm_executor(t_vm *vm)
{
	int		i;
	int		j;

	i = 0;
	while (i < vm->champ_size)
	{
		j = 0;
		while (j < (int)(vm->champ[i].processes->size))
		{
			vm_executor_process(vm,
				&(((t_process*)vm->champ[i].processes->data)[j]));
			j++;
		}
		i++;
	}
}
