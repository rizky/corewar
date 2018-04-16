/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:47:51 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/16 09:47:44 by rnugroho         ###   ########.fr       */
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
		if (ARRAY(a->ops, i).label && ft_strcmp(ARRAY(a->ops, i).label, str) == 0)
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
			if (ARRAY(a->ops, i).params[j].type == T_DIR &&
				ARRAY(a->ops, i).params[j].value == -1)
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
	asm_get_paramtype(int opcode, char *param, int *value, int *size)
{
	if (ft_re_match("^r\\d+$", param) == 0)
	{
		*value = asm_get_paramval(param, "\\d+");
		*size = 1;
		return (T_REG);
	}
	else if (ft_re_match("^%:[\\w_\\d]+$", param) == 0 ||
			ft_re_match("^%[-+]*\\d+$", param) == 0)
	{
		if (ft_re_match("^%:[\\w_\\d]+$", param) == 0 )
			*value = -1;
		else if (ft_re_match("^%[-+]*\\d+$", param) == 0)
			*value = asm_get_paramval(param, "[-+]*\\d+");
		*size = g_op_dict[opcode].d_size;
		return (T_DIR);
	}
	else if (ft_re_match("^[-+]*\\d+$", param) == 0)
	{
		*value = asm_get_paramval(param, "[-+]*\\d+");
		*size = 2;
		return (T_IND);
	}
	else
		return (-1);
}
