/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:47:51 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/13 17:30:23 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int
	ft_get_op(t_asm *a, header_t *h)
{
	char	*func;
	char	*op;
	char	*opcode;
	char	*par1 = NULL;
	char	*par2 = NULL;
	char	*par3 = NULL;

	ft_skip_empty_lines(a);
	func = ft_re_match_capture("^\\w+:[ \t]*\\w+[ \t]+.*",
				"\\w+:", a->file[a->i]);
	op = ft_re_capture("\\w+[ \t]+.*", a->file[a->i]);
	if (op == NULL)
		return (ft_error(OP, -1));
	opcode = ft_re_capture("\\w+", op);
	ft_printfln("function: %s", func);
	ft_printfln("opcode:%s", opcode);
	if (ft_strcmp(opcode, "sti") == 0)
	{
		par1 = ft_re_capture("r\\d+", op);
		par2 = ft_re_capture("%:\\w+", op);
		par3 = ft_re_capture("%\\d+", op);
	}
	else if (ft_strcmp(opcode, "and") == 0)
	{
		par1 = ft_re_capture("r\\d+", op);
		par2 = ft_re_capture("%\\d+", op);
		par3 = ft_re_capture("r\\d+", op);
	}
	else if (ft_strcmp(opcode, "live") == 0)
	{
		par1 = ft_re_capture("%\\d+", op);
	}
	else if (ft_strcmp(opcode, "zjmp") == 0)
	{
		par1 = ft_re_capture("%:\\w+", op);
	}
	ft_printfln("params: %s - %s - %s", par1, par2, par3);
	ft_printfln("---");
	return (0);
}