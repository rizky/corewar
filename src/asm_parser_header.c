/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:56:36 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/16 18:35:01 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"
#include "libft.h"

/*
** To-do: protect ft_re_match_capture in libft (can cause segfault right now)
*/

int		ft_get_name(t_asm *a)
{
	int tmp;

	ft_skip_empty_lines(a);
	if (a->file[a->i] == NULL)
		return (ft_error(HEADER, -1, a->file[a->i]));
	tmp = a->i;
	if ((a->name = ft_re_match_capture("^.name[ \t]*\"[^\"]*\"$", "\"[^\"]*\"",
		a->file[a->i])) == NULL)
	{
		a->i++;
		ft_skip_empty_lines(a);
		if ((a->name = ft_re_match_capture("^.name[ \t]*\"[^\"]*\"$", "\"[^\"]*\"",
			a->file[a->i])) == NULL)
			return (ft_error(HEADER, -1, a->file[a->i]));
	}
	a->i = tmp;
	if (ft_strlen(a->name) == 0)
		a->name = "\0";
	else
		a->name = ft_re_capture("[^\"]+", a->name);
	if (a->name && ft_strlen(a->name) > PROG_NAME_LENGTH)
		return (ft_error(NAME_LEN, -1, a->file[a->i]));
	return (0);
}

int		ft_get_comment(t_asm *a) {
    int prev;
    int tmp;
    char *new;

    tmp = a->i;
    prev = tmp - 1;
    ft_skip_empty_lines(a);
    while (!ft_re_match_capture("^.comment[ \t]*\"[^\"]*\"$", "\"[^\"]*\"", a->file[tmp]))
    {
        new = ft_strjoin(a->file[tmp], a->file[a->i + 1]);
        free(a->file[tmp]);
        a->file[tmp] = new;
        a->i++;
    }
	if ((a->comment = ft_re_match_capture("^.comment[ \t]*\"[^\"]*\"$", "\"[^\"]*\"", a->file[tmp])) == NULL)
		if ((a->comment = ft_re_match_capture("^.comment[ \t]*\"[^\"]*\"$", "\"[^\"]*\"", a->file[prev])) == NULL)
			return (ft_error(HEADER, -1, a->file[tmp]));
	if (ft_strlen(a->comment) == 0)
		a->comment = "\0";
	else
		a->comment = ft_re_capture("[^\"]+", a->comment);
	if (a->comment && ft_strlen(a->comment) > COMMENT_LENGTH)
		return (ft_error(COMMENT_LEN, -1, a->file[tmp]));
	return (0);
}
