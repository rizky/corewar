/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 20:45:41 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/15 12:01:09 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void
	asm_print(t_asm *a)
{
	int	i;
	int	j;

	i = 0;
	ft_printfln("Dumping annotated program on standard output");
	ft_printfln("Program size : %d bytes", a->size);
	ft_printfln("Name : \"%s\"", a->name);
	ft_printfln("Comment : \"%s\"", a->comment);
	while (i < a->op_c)
	{
		if (a->ops[i].func != NULL)
			ft_printfln("%-5d      :\t%s", a->ops[i].offset, a->ops[i].func);
		ft_printf("%-5d(%-3d) :\t    %-10s",
		a->ops[i].offset, a->ops[i].size, a->ops[i].opname);
		j = 0;
		while (j < a->ops[i].param_c)
		{
			ft_printf("%-18s", a->ops[i].params[j].str);
			j++;
		}
		ft_printf("\n");
		ft_printf("         \t    %-10d", a->ops[i].opcode);
		j = 0;
		while (j < a->ops[i].param_c)
		{
			ft_printf("%-18d", a->ops[i].params[j].value);
			j++;
		}
		ft_printf("\n\n");
		i++;
	}
}
