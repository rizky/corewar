/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_uncompiler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 17:34:43 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/06 08:05:35 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

static int	vm_print_asm(t_array *file, char *path)
{
	int		i;
	int		fd;
	char	*cor;

	cor = malloc(sizeof(char) * (ft_strlen(path) + 3));
	if (cor == NULL)
		return (-1);
	ft_bzero(cor, ft_strlen(path) + 3);
	cor = ft_strncpy(cor, path, ft_strlen(path) - 4);
	cor = ft_strcat(cor, "1.s");
	fd = open(cor, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	i = -1;
	ft_printfln("Writing output program to %s", cor);
	while (++i < (int)file->size)
		ft_dprintf(fd, "%c", ((char*)file->data)[i]);
	free(cor);
	return (0);
}

static void	vm_uncompiler_op(t_op op, t_array *file)
{
	int		i;
	int		len;
	char	*temp;

	temp = ft_rasprintf(&len, "%s", g_op_dict[op.opcode].name);
	fta_append_free(file, temp, len);
	i = -1;
	while (++i < op.param_c)
	{
		if (i > 0)
			fta_append_char(file, ',');
		if (op.params[i].type == REG_CODE)
			temp = ft_rasprintf(&len, " r%d", op.params[i].value);
		else if (op.params[i].type == DIR_CODE)
			temp = ft_rasprintf(&len, " %%%d", op.params[i].value);
		else
			temp = ft_rasprintf(&len, " %d", op.params[i].value);
		fta_append_free(file, temp, len);
	}
	fta_append_char(file, '\n');
}

static t_op	vm_uncompiler_param(int *index, char *op_str)
{
	t_op	op;
	int		j;
	int		cursor;

	ft_bzero(&op, sizeof(t_op));
	cursor = *index + 1;
	op.opcode = op_str[*index];
	op.size += g_op_dict[op.opcode].is_oc ? 2 : 1;
	op.oc = (g_op_dict[op.opcode].is_oc) ? op_str[cursor] :
		g_op_dict[op.opcode].p_type[0];
	op.param_c = g_op_dict[op.opcode].param_c;
	j = -1;
	while (++j < op.param_c)
	{
		op.params[j].type = (g_op_dict[op.opcode].is_oc) ?
		(op.oc & (0xC0 >> (j * 2))) >> ((3 - j) * 2) : op.oc;
		(op.params[j].type == REG_CODE) ? op.params[j].size = 1 : 0;
		(op.params[j].type == IND_CODE) ? op.params[j].size = 2 : 0;
		(op.params[j].type == DIR_CODE) ? op.params[j].size =
			g_op_dict[op.opcode].d_size : 0;
		cursor = *index + op.size;
		op.params[j].value = vm_ld(cursor, op.params[j].size, op_str);
		op.size += op.params[j].size;
	}
	return (op);
}

static void	vm_uncompiler_header(t_header header, t_array *file)
{
	char		*temp;
	int			len;

	temp = ft_rasprintf(&len, ".name \"%s\"\n", header.prog_name);
	fta_append_free(file, temp, len);
	temp = ft_rasprintf(&len, ".comment \"%s\"\n", header.comment);
	fta_append_free(file, temp, len);
	fta_append_char(file, '\n');
}

void		vm_uncompiler(t_vm vm)
{
	t_array		file;
	int			index;
	t_op		op;
	int			i;

	i = 0;
	while (i < vm.champ_size)
	{
		file = NEW_ARRAY(char);
		vm_uncompiler_header(vm.champ[i].header, &file);
		index = 0;
		while (index < (int)vm.champ[i].header.prog_size)
		{
			op = vm_uncompiler_param(&index, vm.champ[i].op);
			vm_uncompiler_op(op, &file);
			index += op.size;
		}
		vm_print_asm(&file, vm.champ[i].path);
		fta_clear(&file);
		i++;
	}
}
