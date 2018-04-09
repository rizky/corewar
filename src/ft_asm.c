/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:40:47 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/09 07:43:56 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

void
	asm_print_memory(t_array *binary)
{
	int i;

	i = 0;
	while (i < (int)binary->size)
	{
		ft_printf("%c", ((char*)binary->data)[i]);
		i++;
	}
}

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
}

void
	asm_append_comment(t_array *binary, char *str)
{
	int i;

	i = 0;
	while (i < 8)
	{
		fta_append_char(binary, 0x00);
		i++;
	}
	fta_append(binary, str, ft_strlen(str));
	i = ft_strlen(str) + 8;
	while (i < COMMENT_LENGTH)
	{
		fta_append_char(binary, 0x00);
		i++;
	}
}

void
	asm_append_op(t_array *binary)
{
	int i;

	i = 0;
	while (i < 12)
	{
		fta_append_char(binary, 0x00);
		i++;
	}
	fta_append_char(binary, 0x0b);
	fta_append_char(binary, 0x68);
}

int
	main(int ac, char **av)
{
	t_array	binary;

	(void)ac;
	(void)av;
	binary = NEW_ARRAY(char);
	asm_append_magic_nbr(&binary);
	asm_append_name(&binary, "zork");
	asm_append_comment(&binary, "just a basic living prog");
	asm_append_op(&binary);
	asm_print_memory(&binary);
	return (0);
}