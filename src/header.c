/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:56:36 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/14 13:20:06 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int
	ft_get_name(t_asm *a, header_t *h)
{
	int tmp;
	int next;

	ft_skip_empty_lines(a);
	tmp = a->i;
	a->i++;
	ft_skip_empty_lines(a);
	next = a->i;
	a->i = tmp;
	if ((a->name = ft_re_match_capture("^.name[ \t]*\"[^\"]+\"$", "\".+\"",
		a->file[a->i])) == NULL)
		if ((a->name = ft_re_match_capture("^.name[ \t]*\"[^\"]+\"$", "\".+\"",
			a->file[next])) == NULL)
			return (ft_error(NAME, -1));
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
			return (ft_error(COMMENT, -1));
	a->comment = ft_re_capture("[^\"]+", a->comment);
	if (ft_strlen(a->comment) > COMMENT_LENGTH)
		return (ft_error(COMMENT_LEN, -1));
	ft_memcpy(h->comment, a->comment, ft_strlen(a->comment) + 1);
	return (0);
}
