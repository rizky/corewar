/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:40:47 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/21 23:53:27 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

void
	cw_print_memory(t_array *binary)
{
	int i;

	i = 0;
	while (i < (int)binary->size)
	{
		ft_printf("%c", ((char*)binary->data)[i]);
		i++;
	}
}

void
	cw_append_magic_nbr(t_array *binary)
{
	fta_append_char(binary, 0x00);
	fta_append_char(binary, 0xea);
	fta_append_char(binary, 0x83);
	fta_append_char(binary, 0xf3);
}

void
	cw_append_name(t_array *binary, char *str)
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
	cw_append_comment(t_array *binary, char *str)
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
	cw_append_op(t_array *binary)
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

	binary = NEW_ARRAY(char);
	cw_append_magic_nbr(&binary);
	cw_append_name(&binary, "zork");
	cw_append_comment(&binary, "just a basic living prog");
	cw_append_op(&binary);
	cw_print_memory(&binary);
	return (0);
}