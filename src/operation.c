/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:47:51 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/13 16:57:24 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int
	ft_get_op(t_asm *a, header_t *h)
{
	char	*func;
	char	*op;
	char	*opcode;

	ft_skip_empty_lines(a);
	func = ft_re_match_capture("^\\w+:[ \t]*\\w+[ \t]+.*",
				"\\w+:", a->file[a->i]);
	if (func)
		op = ft_re_match_capture("^\\w+:[ \t]*\\w+[ \t]+.*",
				"\\w+[ \t]+.*", a->file[a->i]);
	else
		op = ft_re_match_capture("\\w+[ \t]+.*",
				"\\w+[ \t]+.*", a->file[a->i]);
	opcode = ft_re_match_capture("\\w+[ \t]+.*",
				"\\w+", op);
	ft_printfln("%s", func);
	ft_printfln("%s", op);
	ft_printfln("%s", opcode);
	return (0);
}