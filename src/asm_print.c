/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 20:45:41 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/18 09:23:17 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

static void
	asm_print_header(t_asm a)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", a.size);
	ft_printf("Name : \"%s\"\n", a.name);
	ft_printf("Comment : \"%s\"\n\n", a.comment);
}

void
	asm_print_big_endian(int value, int size)
{
	int		i;
	int		bits;

	i = 0;
	bits = size * 8;
	while (i <= bits - 8)
	{
		ft_printf("%-3d ", (unsigned char)(value >> (bits - 8 - i)));
		i = i + 8;
	}
	while (i < 32)
	{
		ft_printf("    ");
		i = i + 8;
	}
	ft_printf("  ");
}

void
	asm_print_op(t_asm a, int i)
{
	int	j;

	(g_op_dict[ARRAY(a.ops, i).opcode].is_oc) ?
	ft_printf("                    %-4d%-6d", ARRAY(a.ops, i).opcode,
		ARRAY(a.ops, i).oc) :
	ft_printf("                    %-10d", ARRAY(a.ops, i).opcode);
	j = -1;
	while (++j < ARRAY(a.ops, i).param_c)
		asm_print_big_endian(ARRAY(a.ops, i).params[j].value,
			ARRAY(a.ops, i).params[j].size);
	ft_printf("\n");
	(g_op_dict[ARRAY(a.ops, i).opcode].is_oc) ?
	ft_printf("                    %-4d%-6d", ARRAY(a.ops, i).opcode,
		ARRAY(a.ops, i).oc) :
	ft_printf("                    %-10d", ARRAY(a.ops, i).opcode);
	j = -1;
	while (++j < ARRAY(a.ops, i).param_c)
		ft_printf("%-18d", ARRAY(a.ops, i).params[j].value);
}

void
	asm_print(t_asm a)
{
	int	i;
	int	j;

	asm_print_header(a);
	i = -1;
	while (++i < a.op_c)
	{
		if (ARRAY(a.ops, i).label != NULL)
			ft_printf("%-5d      :    %s:\n", ARRAY(a.ops, i).offset,
			ARRAY(a.ops, i).label);
		if (ARRAY(a.ops, i).opcode != 0)
		{
			ft_printf("%-5d(%-3d) :        %-10s",
			ARRAY(a.ops, i).offset, ARRAY(a.ops, i).size,
			ARRAY(a.ops, i).opname);
			j = -1;
			while (++j < ARRAY(a.ops, i).param_c)
				ft_printf("%-18s", ARRAY(a.ops, i).params[j].str);
			ft_printf("\n");
			asm_print_op(a, i);
			ft_printf("\n\n");
		}
	}
}

int
	asm_print_memory(t_array *binary, char *path)
{
	int		i;
	int		fd;
	char	*cor;

	cor = malloc(sizeof(char) * (ft_strlen(path) + 3));
	if (cor == NULL)
		return (-1);
	ft_bzero(cor, ft_strlen(path) + 3);
	cor = ft_strncpy(cor, path, ft_strlen(path) - 1);
	cor = ft_strcat(cor, "cor");
	fd = open(cor, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	ft_printfln("Writing output program to %s", cor);
	i = -1;
	while (++i < (int)binary->size)
		ft_dprintf(fd, "%c", ((char*)binary->data)[i]);
	free(cor);
	return (0);
}
