/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:47:51 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/14 10:50:41 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

# define PTYPE_REG 0
# define PTYPE_IND 1
# define PTYPE_DIR 2

int
	asm_get_paramtype(char *param)
{
	if (ft_re_match("^r\\d+$", param) == 0)
		return (PTYPE_REG);
	else if (ft_re_match("^%:\\w+$", param) == 0)
		return (PTYPE_IND);
	else if (ft_re_match("^%\\d+$", param) == 0)
		return (PTYPE_DIR);
	else
		return (-1);
}

int
	ft_get_op(t_asm *a, header_t *h)
{
	char	*func;
	char	*op;
	char	*opcode;
	char	*param;
	char	**params;

	(void)h;
	ft_skip_empty_lines(a);
	func = ft_re_match_capture("^\\w+:[ \t]*\\w+[ \t]+.*",
				"\\w+:", a->file[a->i]);
	op = ft_re_capture("\\w+[ \t]+.*", a->file[a->i]);
	if (op == NULL)
		return (ft_error(OP, -1));
	opcode = ft_re_capture("\\w+", op);
	param = ft_re_capture("[^ \t]+", ft_re_capture("\t[^ \t]+", op));
	ft_printfln("function:%s", func);
	ft_printfln("op:%s", op);
	ft_printfln("opcode:%s", opcode);
	params = ft_strsplit(param, ',');
	int i = 0;
	while (params[i])
	{
		ft_printf("param %d: %s ", i, params[i]);
		if (asm_get_paramtype(params[i]) == PTYPE_REG)
			ft_printfln("(Registry)");
		else if (asm_get_paramtype(params[i]) == PTYPE_IND)
			ft_printfln("(Indirect)");
		else if (asm_get_paramtype(params[i]) == PTYPE_DIR)
			ft_printfln("(Direct)");
		i++;
	}
	ft_printfln("---");
	return (0);
}