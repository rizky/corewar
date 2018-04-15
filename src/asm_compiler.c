/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_compiler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 17:34:43 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/15 18:28:32 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

char
	*asm_to_big_endian(int value)
{
	t_array	result;
	int		i;

	i = 0;
	result = NEW_ARRAY(char);
	while (i < 32)
	{
		fta_append_char(&result, (value << i & 0xff000000) >> 24);
		i = i + 8;
	}
	return (result.data);
}

void
	asm_append_magic_nbr(t_array *binary)
{
	char	*magic_nbr;

	magic_nbr = asm_to_big_endian(COREWAR_EXEC_MAGIC);
	fta_append(binary, magic_nbr, 4);
	free(magic_nbr);
}

void
	asm_compiler(t_asm a)
{
	t_array	binary;

	binary = NEW_ARRAY(char);
	asm_append_magic_nbr(&binary);
	asm_append_name(&binary, a.name);
	asm_append_programsize(&binary, 34);
	asm_append_comment(&binary, a.comment);
	asm_print_memory(&binary, a.path);
}