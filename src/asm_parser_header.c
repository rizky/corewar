/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:56:36 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/18 14:26:04 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

static int	asm_get_content_nl(t_asm *a, char **content_str)
{
	t_array content;
	char	*temp;

	if (*content_str != NULL)
		return (-1);
	content = NEW_ARRAY(char);
	temp = ft_re_capture("\".*", a->file[a->i]);
	fta_append_free(&content, temp, ft_strlen(temp));
	a->i++;
	while (a->file[a->i] && ft_re_match(".*\"", a->file[a->i]))
	{
		fta_append_char(&content, '\n');
		fta_append(&content, a->file[a->i], ft_strlen(a->file[a->i]));
		a->i++;
	}
	if (ft_re_match(".*\"$", a->file[a->i]) != 0)
	{
		fta_clear(&content);
		return (-1);
	}
	fta_append_char(&content, '\n');
	fta_append(&content, a->file[a->i], ft_strlen(a->file[a->i]));
	fta_append_char(&content, '\0');
	*content_str = (char *)content.data;
	return (1);
}

int			ft_get_name(t_asm *a)
{
	ft_skip_empty_lines(a);
	if (ft_re_match("^.name[ \t]*\"[^\"]*\"$", a->file[a->i]) != 0)
	{
		if (ft_re_match("^.name[ \t]*\".*$", a->file[a->i]) == 0)
			return (asm_get_content_nl(a, &(a->name)));
		else
			return (-1);
	}
	if (a->name != NULL)
		return (-1);
	a->name = ft_re_capture("\".*\"", a->file[a->i]);
	(!a->name) ? a->name = "\0" : 0;
	return (0);
}

int			ft_get_comment(t_asm *a)
{
	ft_skip_empty_lines(a);
	if (ft_re_match("^.comment[ \t]*\"[^\"]*\"$", a->file[a->i]) != 0)
	{
		if (ft_re_match("^.comment[ \t]*\".*$", a->file[a->i]) == 0)
			return (asm_get_content_nl(a, &(a->comment)));
		else
			return (-1);
	}
	a->comment = ft_re_capture("\".*\"", a->file[a->i]);
	(!a->comment) ? a->comment = "\0" : 0;
	return (0);
}
