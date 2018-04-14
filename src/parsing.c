/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 09:24:11 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/14 19:49:48 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void
	asm_print_asm(t_asm *a)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	while (i < a->op_c)
	{
		if (a->ops[i].func != NULL)
			ft_printfln("%s", a->ops[i].func);
		ft_printf("(%-3d)\t%s\t", a->ops[i].size, a->ops[i].opname);
		j = 0;
		while (j < a->ops[i].param_c)
		{
			ft_printf("%s\t", a->ops[i].params[j].str);
			j++;
		}
		ft_printf("\n");
		ft_printf("\t%d\t", a->ops[i].opcode);
		j = 0;
		size = 0;
		while (j < a->ops[i].param_c)
		{
			ft_printf("%d\t", a->ops[i].params[j].value);
			size += a->ops[i].params[j].size;
			j++;
		}
		ft_printf("\n");
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
	ft_printf("name: %s\n", h->prog_name);
	ft_printf("comment: %s\n", h->comment);
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
