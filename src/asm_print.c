/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 20:45:41 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/15 20:47:35 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

static void
	asm_print_header(t_asm a)
{
	ft_dprintf(2, "Dumping annotated program on standard output\n");
	ft_dprintf(2, "Program size : %d bytes\n", a.size);
	ft_dprintf(2, "Name : \"%s\"\n", a.name);
	ft_dprintf(2, "Comment : \"%s\"\n", a.comment);
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
		if (a.ops[i].label != NULL)
			ft_printf("%-5d      :\t%s:\n", a.ops[i].offset, a.ops[i].label);
		ft_printf("%-5d(%-3d) :\t    %-10s",
		a.ops[i].offset, a.ops[i].size, a.ops[i].opname);
		j = -1;
		while (++j < a.ops[i].param_c)
			ft_printf("%-18s", a.ops[i].params[j].str);
		ft_printf("\n");
		(a.ops[i].param_c > 1) ?
		ft_printf("         \t    %-4d%-6d", a.ops[i].opcode, a.ops[i].oc) :
		ft_printf("         \t    %-10d", a.ops[i].opcode);
		j = -1;
		while (++j < a.ops[i].param_c)
			ft_printf("%-18d", a.ops[i].params[j].value);
		ft_printf("\n\n");
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
	fd = open(cor, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	free(cor);
	i = 0;
	ft_printfln("Writing output program to %s", cor);
	while (i < (int)binary->size)
	{
		ft_dprintf(fd, "%c", ((char*)binary->data)[i]);
		i++;
	}
	return (0);
}
