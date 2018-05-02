/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:45:30 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/02 19:00:38 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_op_live(t_vm *vm, t_process *p)
{
	(void)vm;
	p->live_nbr++;
	if (p->op.params[0].value == ((p->champ + 1) * -1))
	{
		vm->champ[p->champ].live_nbr++;
		vm->last_live_champ = p->champ;
	}
	vm_op_inc(vm, p);
}

void
	vm_live_print(t_process p)
{
	ft_printf("P %4d | ", p.index);
	ft_printf("%s", g_op_dict[p.op.opcode].name);
	ft_printf(" %d", p.op.params[0].value);
	ft_printf("\n");
}

void
	vm_op_inc(t_vm *vm, t_process *p)
{
	int val;

	(void)vm;
	if (p->op.opcode != 0)
		p->pc = p->pc_next;
	else
		p->pc++;
	if (p->offset + p->pc >= MEM_SIZE)
	{
		val = p->offset + p->pc - MEM_SIZE;
		p->pc = (p->offset - val) * -1;
	}
}

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
				ft_printf(" %hd", p.reg[p.op.params[i].value]);
			else
				ft_printf(" r%d", p.op.params[i].value);
		else
			ft_printf(" %hd", p.op.params[i].value);
	ft_printf("\n");
}
