/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_compiler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 17:34:43 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/16 21:29:02 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

char
	*asm_to_big_endian(int value, int size)
{
	t_array	result;
	int		i;
	int		bits;

	i = 0;
	result = NEW_ARRAY(char);
	bits = size * 8;
	while (i <= bits - 8)
	{
		fta_append_char(&result, value >> (bits - 8 - i));
		i = i + 8;
	}
	return (result.data);
}

void
	asm_append_magic_nbr(t_array *binary)
{
	fta_append_free(binary, asm_to_big_endian(COREWAR_EXEC_MAGIC, 4), 4);
}

void
	asm_append_op(t_array *binary, t_op op)
{
	int		i;

	if (op.opcode == 0)
		return ;
	fta_append_free(binary, asm_to_big_endian(op.opcode, 1), 1);
	if (op.param_c > 1)
		fta_append_free(binary, asm_to_big_endian(op.oc, 1), 1);
	i = -1;
	while (++i < op.param_c)
		fta_append_free(binary, asm_to_big_endian(op.params[i].value,
					op.params[i].size), op.params[i].size);
}

void
	asm_compiler(t_asm a)
{
	t_array	binary;
	int		i;

	binary = NEW_ARRAY(char);
	asm_append_magic_nbr(&binary);
	asm_append_name(&binary, a.name);
	asm_append_size(&binary, a.size);
	asm_append_comment(&binary, a.comment);
	i = -1;
	while (++i < a.op_c)
		asm_append_op(&binary, ARRAY(a.ops, i));
	asm_print_memory(&binary, a.path);
}
