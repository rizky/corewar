/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:47:51 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/14 18:25:18 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

typedef struct	s_op_dict
{
	char		*name;
	int			opcode;
}				t_op_dict;

static	t_op_dict g_op_dict[16]={
    { .name = "live", 	.opcode = 0x01 },
    { .name = "ld", 	.opcode = 0x02 },
    { .name = "st", 	.opcode = 0x03 },
    { .name = "add", 	.opcode = 0x04 },
	{ .name = "sub", 	.opcode = 0x05 },
	{ .name = "and", 	.opcode = 0x06 },
	{ .name = "or", 	.opcode = 0x07 },
	{ .name = "xor", 	.opcode = 0x08 },
	{ .name = "zjmp", 	.opcode = 0x09 },
	{ .name = "ldi", 	.opcode = 0x0a },
	{ .name = "sti", 	.opcode = 0x0b },
	{ .name = "fork", 	.opcode = 0x0c },
	{ .name = "lld", 	.opcode = 0x0d },
	{ .name = "lldi", 	.opcode = 0x0e },
	{ .name = "lfork", 	.opcode = 0x0f },
	{ .name = "aff", 	.opcode = 0x10 }
};

int
	asm_get_opcode(char	*opname)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(g_op_dict[i].name, opname) == 0)
			return (g_op_dict[i].opcode);
		i++;
	}
	return (-1);
}

int
	asm_get_paramtype(char *param)
{
	if (ft_re_match("^r\\d+$", param) == 0)
		return (T_REG);
	else if (ft_re_match("^%:\\w+$", param) == 0)
		return (T_IND);
	else if (ft_re_match("^%\\d+$", param) == 0)
		return (T_DIR);
	else
		return (-1);
}

int
	ft_get_op(t_asm *a, header_t *h)
{
	char	*func;
	char	*op_str;
	char	*opcode;
	char	*param;
	char	**params;
	t_op	op;
	t_param	par;

	(void)h;
	ft_skip_empty_lines(a);
	func = ft_re_match_capture("^\\w+:[ \t]*\\w+[ \t]+.*",
				"\\w+:", a->file[a->i]);
	op_str = ft_re_capture("\\w+[ \t]+.*", a->file[a->i]);
	if (op_str == NULL)
		return (ft_error(OP, -1));
	opcode = ft_re_capture("\\w+", op_str);
	param = ft_re_capture("[^ \t]+", ft_re_capture("\t[^ \t]+", op_str));
	ft_printfln("function:%s", func);
	ft_printfln("op:%s", op_str);
	ft_printfln("opcode:%s (0x%02x)", opcode, asm_get_opcode(opcode));
	params = ft_strsplit(param, ',');
	op.param_c = 0;
	while (params[op.param_c])
	{
		ft_printf("param %d: %s ", op.param_c, params[op.param_c]);
		if (asm_get_paramtype(params[op.param_c]) == PTYPE_REG)
			ft_printfln("(Registry)");
		else if (asm_get_paramtype(params[op.param_c]) == PTYPE_IND)
			ft_printfln("(Indirect)");
		else if (asm_get_paramtype(params[op.param_c]) == PTYPE_DIR)
			ft_printfln("(Direct)");
		par.str = params[op.param_c];
		par.type = asm_get_paramtype(params[op.param_c]);
		op.params[op.param_c] = par;
		op.param_c++;
	}
	a->ops[a->op_c] = op;
	ft_printfln("---");
	return (0);
}