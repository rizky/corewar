/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:47:51 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/15 16:22:14 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_asm.h"
#include "../libft/include/libft.h"

int
	asm_get_indvalue(t_asm *a, char *label)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_re_capture("[\\w_\\d]+", label);
	while (i < a->op_c)
	{
		if (a->ops[i].label && ft_strcmp(a->ops[i].label, str) == 0)
			return (a->ops[i].offset);
		i++;
	}
	return (-1);
}

int
	asm_populate_indvalue(t_asm *a)
{
	int	i;
	int	j;
	int	offset;

	i = 0;
	while (i < a->op_c)
	{
		j = 0;
		while (j < a->ops[i].param_c)
		{
			if (a->ops[i].params[j].type == T_DIR && a->ops[i].params[j].value == -1)
			{
				offset = asm_get_indvalue(a, a->ops[i].params[j].str);
				if (offset == -1)
					return (ft_error(LABEL_MISSING, -1, a->ops[i].params[j].str));
				a->ops[i].params[j].value =
				asm_get_indvalue(a, a->ops[i].params[j].str) - a->ops[i].offset;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int
	asm_calculate_oc(t_param params[3])
{
	return (params[0].type << 6 | params[1].type << 4 | params[2].type << 2);
}