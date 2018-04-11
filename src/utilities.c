/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 09:45:37 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/11 14:35:33 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_handle_comments(char **file)
{
	int i;
	int j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (file[i][j] == COMMENT_CHAR || file[i][j] == ';')
				file[i][j] = '\0';
			j++;
		}
		i++;
	}
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
	while (a->file[a->i] && ft_line_is_empty(a) && a->file[a->i + 1])
		a->i++;
}

void	ft_trim_file(char **file)
{
	int		i;
	char	*tmp;

	i = 0;
	while (file[i])
	{
		tmp = ft_strtrim(file[i]);
		free(file[i]);
		file[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
}
