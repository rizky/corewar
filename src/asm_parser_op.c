/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:47:51 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/18 23:12:38 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

static int	asm_parser_opcode(char *opname)
{
	int i;

	if (!opname)
		return (0);
	i = 1;
	while (i < 17)
	{
		if (ft_strcmp(g_op_dict[i].name, opname) == 0)
			return (g_op_dict[i].opcode);
		i++;
	}
	return (-1);
}

static char	*asm_parser_opname(char *line)
{
	char	*opstr;
	char	*opname;

	opstr = ft_re_capture("\\w+[ \t%]+.*", line);
	opname = ft_re_capture("\\w+", opstr);
	free(opstr);
	return (opname);
}

static char	**asm_parser_opparam_tab(char *line)
{
	char	*opstr;
	char	*opparam;
	char	*temp;
	char	**param_tab;

	opstr = ft_re_capture("\\w+[ \t]+.*", line);
	temp = ft_re_capture("[\t ]+.+", opstr);
	if (temp == NULL)
	{
		opstr = ft_re_capture("\\w+[ \t]*.*", line);
		temp = ft_re_capture("%.+", opstr);
	}
	opparam = ft_re_capture(".+", temp);
	param_tab = ft_strsplit(opparam, SEPARATOR_CHAR);
	free(opstr);
	free(temp);
	free(opparam);
	return (param_tab);
}

static void	asm_parser_opparam(char *line, t_op *op)
{
	char	**param_tab;
	t_param	par;

	param_tab = asm_parser_opparam_tab(line);
	(*op).param_c = 0;
	while (param_tab && param_tab[(*op).param_c])
	{
		if ((*op).param_c < 3)
		{
			par.str = (ft_re_match("[ \t]*[^ \t]+[ \t]+[^ \t]+[ \t]*",
				param_tab[(*op).param_c]) == 0) ? ft_strdup("N/A") :
				ft_re_capture("[^\t ]+", param_tab[(*op).param_c]);
			par.is_label = 0;
			par.type = asm_get_paramtype((*op).opcode, &par);
			(*op).params[(*op).param_c] = par;
			(*op).size += par.size;
		}
		(*op).param_c++;
	}
	if (param_tab)
		ft_strtab_free(param_tab);
}

int			asm_parser_op(t_asm *a)
{
	t_op	op;
	char	*temp;

	if (ft_re_match("^.+:[ \t]*\\w+[ \t]+.*", a->file[a->i]) == -1)
		if (ft_re_match("^\\w+[^:][ \t]*.*", a->file[a->i]) == -1)
			if (ft_re_match("^[\\w_\\d]+:[ \t]*$", a->file[a->i]) == -1)
				return (ft_error(OP, -1, a->file[a->i]));
    if (ft_re_match("^\\w+[^:][ \t]*$", a->file[a->i]) != -1)
        return (ft_error(OP, -1, a->file[a->i]));
    if (ft_re_match(",,", a->file[a->i]) != -1 ||
		ft_re_match(",[ \t]*$", a->file[a->i]) != -1)
		return (ft_error(OP, -1, a->file[a->i]));
	temp = ft_re_capture("^[^% \t]+:", a->file[a->i]);
	op.label = ft_re_capture("[^:]+", temp);
	op.opname = asm_parser_opname(a->file[a->i]);
	op.opcode = asm_parser_opcode(op.opname);
	op.size = 0;
	op.offset = a->size;
	asm_parser_opparam(a->file[a->i], &op);
	op.oc = asm_calculate_oc(op.params, op.param_c);
	if (op.opcode > 0)
		op.size += g_op_dict[op.opcode].is_oc ? 2 : 1;
	fta_append(a->ops, &op, 1);
	a->size += op.size;
	free(temp);
	return (0);
}
