/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:11:09 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/18 14:48:14 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int		ft_free_asm(t_asm *a, int status)
{
	int	i;
	int	j;

	(a->name && (a->name)[0] != '\0') ? free(a->name) : 0;
	(a->comment && (a->comment)[0] != '\0') ? free(a->comment) : 0;
	i = -1;
	while (++i < (int)a->ops->size)
	{
		if (ARRAY(a->ops, i).label != NULL)
			free(ARRAY(a->ops, i).label);
		if (ARRAY(a->ops, i).opcode != 0)
		{
			free(ARRAY(a->ops, i).opname);
			j = -1;
			while (++j < ARRAY(a->ops, i).param_c)
				free(ARRAY(a->ops, i).params[j].str);
		}
	}
	fta_clear(a->ops);
	ft_free_tab(a->file, status);
	return (status);
}

int		ft_free_tab(char **tab, int status)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (status);
}

int		ft_free(char *str, int status)
{
	free(str);
	return (status);
}
