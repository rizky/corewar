/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 09:24:11 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/14 20:23:46 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void
	asm_print_asm(t_asm *a)
{
	int	i;
	int	j;
	int offset;

	i = 0;
	offset = 0;
	ft_printfln("Dumping annotated program on standard output");
	ft_printfln("Program size : %d bytes", a->size);
	ft_printfln("Name : \"%s\"", a->name);
	ft_printfln("Comment : \"%s\"", a->comment);
	while (i < a->op_c)
	{
		if (a->ops[i].func != NULL)
			ft_printfln("%-5d      :\t%s", offset, a->ops[i].func);
		ft_printf("%-5d(%-3d) :\t    %-10s", offset, a->ops[i].size, a->ops[i].opname);
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
		offset += a->ops[i].size;
		i++;
	}
}
int		ft_parsing(t_asm *a, header_t *h)
{
	ft_handle_comments(a->file);
	ft_trim_file(a->file);
	if (ft_get_name(a, h) == -1)
		return (-1);
	a->i++;
	if (ft_get_comment(a, h) == -1)
		return (-1);
	a->i++;
	while (a->file[a->i])
	{
		ft_get_op(a);
		a->op_c++;
		a->i++;
	}
	asm_print_asm(a);
	return (0);
}
