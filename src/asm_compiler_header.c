/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_compiler_header.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 18:08:15 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/15 18:53:33 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

void
	asm_append_nullbyte(t_array *binary)
{
	char	*nullbyte;

	nullbyte = asm_to_big_endian(0x0);
	fta_append(binary, nullbyte, 4);
	free(nullbyte);
}

void
	asm_append_name(t_array *binary, char *str)
{
	int i;

	fta_append(binary, str, ft_strlen(str));
	i = ft_strlen(str);
	while (i < PROG_NAME_LENGTH)
	{
		fta_append_char(binary, 0x00);
		i++;
	}
	asm_append_nullbyte(binary);
}

void
	asm_append_comment(t_array *binary, char *str)
{
	int i;

	fta_append(binary, str, ft_strlen(str));
	i = ft_strlen(str);
	while (i < COMMENT_LENGTH)
	{
		fta_append_char(binary, 0x00);
		i++;
	}
	asm_append_nullbyte(binary);
}

void
	asm_append_programsize(t_array *binary, int size)
{
	char	*psize;

	psize = asm_to_big_endian(size);
	fta_append(binary, psize, 4);
	free(psize);
}
