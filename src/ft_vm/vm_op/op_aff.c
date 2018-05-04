/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:01:21 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/04 22:48:55 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_op_aff(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
	vm_op_inc(vm, p);
}

void	vm_aff_print(t_process p)
{
	if (p.op.params[0].value < 1 || p.op.params[0].value > 16)
		return ;
	ft_printfln("Aff: %c", p.reg[p.op.params[0].value]);
}
