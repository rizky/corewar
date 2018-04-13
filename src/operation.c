/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:47:51 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/13 18:21:45 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
		ft_printfln("param %d: %s", i, params[i]);
		i++;
	}
	ft_printfln("---");
	return (0);
}