/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_labels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:04:48 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/15 14:36:33 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"
#include "libft.h"

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
		if (ft_is_label(a->file[i])) //regarde si on a un  : dans le debut de ligne
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
	if ((count = ft_count_labels(a)) == -1) //compte les labels dans le fichier
		return (-1);
	if ((a->labels = (char**)malloc(sizeof(char*) * count + 1)) == NULL)
		return (ft_error(MALLOC, -1, a->file[i]));
	while (a->file[i])
	{
		if (ft_is_label(a->file[i])) //regarde si il y a un : dans le debut de la ligne
		{
			a->labels[j] = ft_strcdup(a->file[i], LABEL_CHAR); //dup le nom du label
			j++;
		}
		i++;
	}
	a->labels[j] = 0;
	return (0);
}
