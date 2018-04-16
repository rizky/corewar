/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helper_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 09:45:37 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/16 17:49:19 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"
#include "libft.h"

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
