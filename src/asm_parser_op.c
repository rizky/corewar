/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:47:51 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/15 23:08:22 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_asm.h"
#include "../libft/include/libft.h"

int
	asm_parser_opcode(char *opname)
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

char
	*asm_parser_opname(char *line)
{
	char	*opstr;
	char	*opname;
	opstr = ft_re_capture("\\w+[ \t]+.*", line); //capture par le label mais apres
	opname = ft_re_capture("\\w+", opstr); //chope sti
	free(opstr);
	return (opname);
}

void
	asm_parser_opparam(char *line, t_op *op)
{
	char	*opstr;
	char	*opparam;
	char	*temp;
	char	**param_tab;
	t_param	par;

	opstr = ft_re_capture("\\w+[ \t]+.*", line); //sans le labal
	temp = ft_re_capture("[\t ][^ \t]+", opstr); //registre
	opparam = ft_re_capture("[^ \t]+", temp); //registre aussi
	param_tab = ft_strsplit(opparam, ',');
	while (param_tab[(*op).param_c])
	{
		par.str = param_tab[(*op).param_c]; //registre
		par.type = asm_get_paramtype((*op).opcode, par.str,
			&(par.value), &(par.size));
		(*op).params[(*op).param_c] = par;
		(*op).param_c++;
		(*op).size += par.size;
	}
	free(opstr);
	free(temp);
	free(opparam);
}

int
	asm_parser_op(t_asm *a)
{
	t_op	op;
	char	*temp;

	ft_skip_empty_lines(a);
	if (ft_re_match("^[\\w_\\d]+:[ \t]*\\w+[ \t]+.*", a->file[a->i]) == -1)
		if (ft_re_match("^\\w+[ \t]+.*", a->file[a->i]) == -1)
			return (ft_error(OP, -1, a->file[a->i]));
	temp = ft_re_capture("\\w+:", a->file[a->i]); //capture le label
	op.label = ft_re_capture("\\w+", temp); // capture le label
	op.param_c = 0;
	op.opname = asm_parser_opname(a->file[a->i]); //chope sti
	if ((op.opcode = asm_parser_opcode(op.opname)) == -1) //chope le code correspondant
		return (-1);
	op.size = 0;
	op.offset = a->size;
	asm_parser_opparam(a->file[a->i], &op);
	op.oc = asm_calculate_oc(op.params, op.param_c);
	op.size += (op.param_c > 1) ? 2 : 1;
	fta_append(a->ops, &op, 1);
	a->size += op.size;
	free(temp);
	return (0);
}
