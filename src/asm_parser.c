/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 09:24:11 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/15 17:44:28 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int
	asm_check_op(t_asm *a)
{
	int i;

	i = 0;
	if (a->ops[a->op_c].opcode == -1)
		return (ft_error(OP, -1, a->file[a->i]));
	while (i < a->ops[a->op_c].param_c)
	{
		if (a->ops[a->op_c].params[i].type == -1)
			return (ft_error(OP_PARAM, -1, a->file[a->i]));
		i++;
	}
	return (0);
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
//	ft_check_instructions(a);
	while (a->file[a->i])
	{
		asm_parser_op(a);
		if (asm_check_op(a) == -1)
			return (-1);
		a->op_c++;
		a->i++;
	}
	if (asm_populate_indvalue(a) == -1)
		return (-1);
	return (0);
}
