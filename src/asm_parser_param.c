/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:47:51 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/16 15:04:41 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int
	asm_get_directval(t_asm *a, char *label)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_re_capture("[\\w_\\d]+", label);
	while (i < a->op_c)
	{
		if (ARRAY(a->ops, i).label &&
			ft_strcmp(ARRAY(a->ops, i).label, str) == 0)
			return (ARRAY(a->ops, i).offset);
		i++;
	}
	return (-1);
}

int
	asm_populate_directval(t_asm *a)
{
	int	i;
	int	j;
	int	offset;

	i = 0;
	while (i < a->op_c)
	{
		j = 0;
		while (j < ARRAY(a->ops, i).param_c)
		{
			if (ARRAY(a->ops, i).params[j].type == DIR_CODE &&
				ARRAY(a->ops, i).params[j].is_label)
			{
				offset = asm_get_directval(a, ARRAY(a->ops, i).params[j].str);
				if (offset == -1)
					return (ft_error(LABEL_MISSING, -1, ARRAY(a->ops, i).params[j].str));
				ARRAY(a->ops, i).params[j].value =
				asm_get_directval(a, ARRAY(a->ops, i).params[j].str) -
								ARRAY(a->ops, i).offset;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int
	asm_calculate_oc(t_param params[3], int param_c)
{
	while (param_c < 3)
	{
		params[param_c].type = 0;
		param_c++;
	}
	return (params[0].type << 6 | params[1].type << 4 | params[2].type << 2);
}

static int
	asm_get_paramval(char *param, char *pattern)
{
	char	*temp;
	int		value;

	temp = ft_re_capture(pattern, param);
	value = ft_atoi(temp);
	free(temp);
	return (value);
}

int
	asm_get_paramtype(int opcode, t_param *param)
{
	if (ft_re_match("^r\\d+$", (*param).str) == 0)
	{
		(*param).value = asm_get_paramval((*param).str, "\\d+");
		(*param).size = 1;
		return (REG_CODE);
	}
	else if (ft_re_match("^%:[\\w_\\d]+$", (*param).str) == 0 ||
			ft_re_match("^%[-+]*\\d+$", (*param).str) == 0)
	{
		(*param).is_label = 0;
		if (ft_re_match("^%:[\\w_\\d]+$", (*param).str) == 0)
			(*param).is_label = 1;
		else if (ft_re_match("^%[-+]*\\d+$", (*param).str) == 0)
			(*param).value = asm_get_paramval((*param).str, "[-+]*\\d+");
		(*param).size = g_op_dict[opcode].d_size;
		return (DIR_CODE);
	}
	else if (ft_re_match("^[-+]*\\d+$", (*param).str) == 0)
	{
		(*param).value = asm_get_paramval((*param).str, "[-+]*\\d+");
		(*param).size = 2;
		return (IND_CODE);
	}
	else
		return (-1);
}
