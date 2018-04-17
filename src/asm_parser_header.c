/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:56:36 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/17 10:27:24 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int
	ft_get_name(t_asm *a)
{
	char *temp;

	ft_skip_empty_lines(a);
	if (ft_re_match("^.name[ \t]+\"[^\"]*\"$", a->file[a->i]) != 0)
		return (-1);
	if (a->name != NULL)
		return (-1);
	temp = ft_re_capture("\".+\"", a->file[a->i]);
	a->name = ft_re_capture("[^\"]+", temp);
	(!a->name)? a->name = "\0": 0;
	free(temp);
	return (0);
}

int
	ft_get_comment(t_asm *a)
{
	char *temp;

	ft_skip_empty_lines(a);
	if (ft_re_match("^.comment[ \t]+\"[^\"]*\"$", a->file[a->i]) != 0)
		return (-1);
	if (a->comment != NULL)
		return (-1);
	temp = ft_re_capture("\".+\"", a->file[a->i]);
	a->comment = ft_re_capture("[^\"]+", temp);
	(!a->comment)? a->comment = "\0": 0;
	free(temp);
	return (0);
}
