/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:56:36 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/14 20:50:53 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

/*
** To-do: protect ft_re_match_capture in libft (can cause segfault right now)
*/

int
	ft_get_name(t_asm *a, header_t *h)
{
	int tmp;

	ft_skip_empty_lines(a);
	tmp = a->i;
	if ((a->name = ft_re_match_capture("^.name[ \t]*\"[^\"]+\"$", "\".+\"",
		a->file[a->i])) == NULL)
	{
		a->i++;
		ft_skip_empty_lines(a);
		if ((a->name = ft_re_match_capture("^.name[ \t]*\"[^\"]+\"$", "\".+\"",
			a->file[a->i])) == NULL)
			return (ft_error(HEADER, -1));
	}
	a->i = tmp;
	a->name = ft_re_capture("[^\"]+", a->name);
	if (ft_strlen(a->name) > PROG_NAME_LENGTH)
		return (ft_error(NAME_LEN, -1));
	ft_memcpy(h->prog_name, a->name, ft_strlen(a->name) + 1);
	return (0);
}

int
	ft_get_comment(t_asm *a, header_t *h)
{
	int prev;

	prev = a->i - 1;
	ft_skip_empty_lines(a);
	if ((a->comment = ft_re_match_capture("^.comment[ \t]*\"[^\"]*\"$",
		"\".*\"", a->file[a->i])) == NULL)
		if ((a->comment = ft_re_match_capture("^.comment[ \t]*\"[^\"]*\"$",
			"\".*\"", a->file[prev])) == NULL)
			return (ft_error(HEADER, -1));
	a->comment = ft_re_capture("[^\"]+", a->comment);
	if (ft_strlen(a->comment) > COMMENT_LENGTH)
		return (ft_error(COMMENT_LEN, -1));
	ft_memcpy(h->comment, a->comment, ft_strlen(a->comment) + 1);
	return (0);
}
