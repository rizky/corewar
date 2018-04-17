/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helper_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 09:45:37 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/17 11:59:25 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int		ft_filename_extension(char *file)
{
	if (file[ft_strlen(file) - 1] == 's' && file[ft_strlen(file) - 2] == '.')
		return (1);
	return (0);
}

int		ft_file_is_empty(char *file)
{
	int i;

	i = 0;
	while (file[i])
	{
		if (file[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int		ft_line_is_empty(t_asm *a)
{
	int j;

	j = 0;
	while (a->file[a->i][j])
	{
		if (!ft_isspace(a->file[a->i][j]))
			return (0);
		j++;
	}
	return (1);
}

void	ft_skip_empty_lines(t_asm *a)
{
	while (a->file[a->i] && ft_line_is_empty(a))
		a->i++;
}
