/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:01:21 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/03 11:26:24 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	vm_op_aff(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}

void	vm_aff_print(t_process p)
{
	ft_printfln("Aff: %c", p.reg[p.op.params[0].value]);
}
