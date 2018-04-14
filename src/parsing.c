/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 09:24:11 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/14 11:09:54 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_parsing(t_asm *a, header_t *h)
{
	ft_handle_comments(a->file);
	ft_trim_file(a->file);
	if (ft_get_name(a, h) == -1)
		return (-1);
	a->i++;
	if (ft_get_comment(a, h) == -1)
		return (-1);
	ft_printf("name: %s\n", h->prog_name);
	ft_printf("comment: %s\n", h->comment);
	a->i++;
	while (a->file[a->i])
	{
		ft_get_op(a, h);
		a->op_counter++;
		a->i++;
	}
	return (0);
}
