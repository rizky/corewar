/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_instructions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 10:22:53 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/15 13:00:20 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int		ft_is_label(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != LABEL_CHAR)
	{
		if (!ft_strchr(LABEL_CHARS, line[i]))
			return (0);
		i++;
		if (line[i] == LABEL_CHAR)
			return (1);
	}
	return (0);
}

int		ft_count_labels(t_asm *a)
{
	int i;
	int labels;

	i = a->i;
	labels = 0;
	while (a->file[i])
	{
		if (a->file[i][0] == LABEL_CHAR)
			return (-1);
		if (ft_is_label(a->file[i]))
			labels++;
		i++;
	}
	return (labels);
}

int		ft_get_labels(t_asm *a)
{
	int i;
	int j;
	int count;

	i = a->i;
	j = 0;
	if ((count = ft_count_labels(a)) == -1)
		return (-1);
	if ((a->labels = (char**)malloc(sizeof(char*) * count + 1)) == NULL)
		return (ft_error(MALLOC, -1, NULL));
	while (a->file[i])
	{
		if (ft_is_label(a->file[i]))
		{
			a->labels[j] = ft_strcdup(a->file[i], LABEL_CHAR);
			j++;
		}
		i++;
	}
	a->labels[j] = 0;
	return (0);
}

int		ft_check_instructions(t_asm *a)
{
	int start;

	ft_skip_empty_lines(a);
	start = a->i;
	if (ft_get_labels(a) == -1)
		ft_dprintf(2, "Error - label\n");
	ft_print_tab(a->labels);
	ft_free_tab(a->labels, 0);
	return (0);
}
