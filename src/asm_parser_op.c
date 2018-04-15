/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:47:51 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/15 12:35:43 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

typedef struct	s_op_dict
{
	char		*name;
	int			opcode;
	int			d_size;
}				t_op_dict;

static	t_op_dict g_op_dict[17] = {
	{ .name = "\0", .opcode = 0x00, .d_size = 0 },
	{ .name = "live", .opcode = 0x01, .d_size = 4 },
	{ .name = "ld", .opcode = 0x02, .d_size = 4 },
	{ .name = "st", .opcode = 0x03, .d_size = 0 },
	{ .name = "add", .opcode = 0x04, .d_size = 0 },
	{ .name = "sub", .opcode = 0x05, .d_size = 0 },
	{ .name = "and", .opcode = 0x06, .d_size = 4 },
	{ .name = "or", .opcode = 0x07, .d_size = 4 },
	{ .name = "xor", .opcode = 0x08, .d_size = 4 },
	{ .name = "zjmp", .opcode = 0x09, .d_size = 2 },
	{ .name = "ldi", .opcode = 0x0a, .d_size = 2 },
	{ .name = "sti", .opcode = 0x0b, .d_size = 2 },
	{ .name = "fork", .opcode = 0x0c, .d_size = 2 },
	{ .name = "lld", .opcode = 0x0d, .d_size = 4 },
	{ .name = "lldi", .opcode = 0x0e, .d_size = 2 },
	{ .name = "lfork", .opcode = 0x0f, .d_size = 2 },
	{ .name = "aff", .opcode = 0x10, .d_size = 0 }
};

int
	asm_get_opcode(char *opname)
{
	int i;

	i = 1;
	while (i < 17)
	{
		if (ft_strcmp(g_op_dict[i].name, opname) == 0)
			return (g_op_dict[i].opcode);
		i++;
	}
	return (-1);
}

int
	asm_get_paramtype(int opcode, char *param, int *value, int *size)
{
	char *temp;

	if (ft_re_match("^r\\d+$", param) == 0)
	{
		temp = ft_re_capture("\\d+", param);
		*value = ft_atoi(temp);
		free(temp);
		*size = 1;
		return (T_REG);
	}
	else if (ft_re_match("^%:\\w+$", param) == 0)
	{
		*value = 0;
		*size = 2;
		return (T_IND);
	}
	else if (ft_re_match("^%\\d+$", param) == 0)
	{
		temp = ft_re_capture("\\d+", param);
		*value = ft_atoi(temp);
		free(temp);
		*size = g_op_dict[opcode].d_size;
		return (T_DIR);
	}
	else
		return (-1);
}

int
	ft_get_op(t_asm *a)
{
	char	*label;
	char	*opstr;
	char	*opname;
	char	*param;
	char	**param_tab;
	t_op	op;
	t_param	par;

	ft_skip_empty_lines(a);
	label = ft_re_match_capture("^\\w+:[ \t]*\\w+[ \t]+.*",
				"\\w+", a->file[a->i]);
	opstr = ft_re_capture("\\w+[ \t]+.*", a->file[a->i]);
	if (opstr == NULL)
		return (ft_error(OP, -1));
	opname = ft_re_capture("\\w+", opstr);
	param = ft_re_capture("[^ \t]+", ft_re_capture("\t[^ \t]+", opstr));
	param_tab = ft_strsplit(param, ',');
	op.param_c = 0;
	op.opname = opname;
	op.opcode = asm_get_opcode(opname);
	op.label = label;
	op.size = 0;
	op.offset = a->size;
	while (param_tab[op.param_c])
	{
		par.str = param_tab[op.param_c];
		par.type = asm_get_paramtype(op.opcode, param_tab[op.param_c],
			&(par.value), &(par.size));
		op.params[op.param_c] = par;
		op.param_c++;
		op.size += par.size;
	}
	op.size += (op.param_c > 1) ? 2 : 1;
	a->ops[a->op_c] = op;
	a->size += op.size;
	return (0);
}
