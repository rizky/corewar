/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 09:24:11 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/15 13:04:15 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int		asm_get_indvalue(t_asm *a, char *label)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_re_capture("\\w+", label);
	while (i < a->op_c)
	{
		if (a->ops[i].label && ft_strcmp(a->ops[i].label, str) == 0)
			return (a->ops[i].offset);
		i++;
	}
	return (-1);
}

int		asm_copulate_indvalue(t_asm *a)
{
	int	i;
	int	j;

	i = 0;
	while (i < a->op_c)
	{
		j = 0;
		while (j < a->ops[i].param_c)
		{
			if (a->ops[i].params[j].type == T_IND)
			{
				a->ops[i].params[j].value =
				asm_get_indvalue(a, a->ops[i].params[j].str) - a->ops[i].offset;
				if (a->ops[i].params[j].value == -1)
					return (ft_error(LABEL_MISSING, -1, a->ops[i].params[j].str));
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		ft_parsing(t_asm *a, header_t *h)
{
	ft_handle_comments(a->file);
	ft_trim_file(a->file);
	if (ft_get_name(a, h) == -1)
		return (-1);
	a->i++;
	if (ft_get_comment(a, h) == -1)
		return (-1);
	a->i++;
//	ft_check_instructions(a);
	while (a->file[a->i])
	{
		if (asm_get_op(a) == -1)
			return (-1);
		a->op_c++;
		a->i++;
	}
	if (asm_copulate_indvalue(a) == -1)
		return (-1);
	asm_print(a);
	return (0);
}
