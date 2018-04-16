/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 09:24:11 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/16 21:46:27 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int		asm_check_op(t_asm *a)
{
	int i;

	i = 0;
	if (ARRAY(a->ops, a->op_c).label != NULL &&
		ARRAY(a->ops, a->op_c).opcode == 0)
		return (0);
	if (ARRAY(a->ops, a->op_c).param_c !=
		g_op_dict[ARRAY(a->ops, a->op_c).opcode].param_c)
		return (ft_error(OP_PARAM, -1, a->file[a->i]));
	if (ARRAY(a->ops, a->op_c).opcode == -1)
		return (ft_error(OP_NAME, -1, a->file[a->i]));
	while (i < ARRAY(a->ops, a->op_c).param_c)
	{
		if (ARRAY(a->ops, a->op_c).params[i].type == -1)
			return (ft_error(OP_PARAM, -1, a->file[a->i]));
		if ((ARRAY(a->ops, a->op_c).params[i].type &
			g_op_dict[ARRAY(a->ops, a->op_c).opcode].p_type[i]) !=
			ARRAY(a->ops, a->op_c).params[i].type)
			return (ft_error(OP_PARAM_TYPE, -1, a->file[a->i]));
		if (ARRAY(a->ops, a->op_c).params[i].type == T_REG &&
			ARRAY(a->ops, a->op_c).params[i].value >99)
			return (ft_error(OP_PARAM_TYPE, -1, a->file[a->i]));
		i++;
	}
	return (0);
}

int		ft_parsing(t_asm *a)
{
	ft_handle_comments(a->file);
	ft_trim_file(a->file);
	if (ft_get_name(a) == -1)
		return (-1);
	a->i++;
	if (ft_get_comment(a) == -1)
		return (-1);
	a->i++;
//	ft_check_instructions(a);
	ft_skip_empty_lines(a);
	while (a->file[a->i])
	{
		if (asm_parser_op(a) == -1)
			return (-1);
		if (asm_check_op(a) == -1)
			return (-1);
		a->op_c++;
		a->i++;
		ft_skip_empty_lines(a);
	}
	if (a->size == 0)
		return (ft_error(OP_EMPTY, -1, NULL));
	if (asm_populate_directval(a) == -1)
		return (-1);
	return (0);
}
