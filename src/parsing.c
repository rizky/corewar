/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 09:24:11 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/11 10:03:58 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_get_name(t_asm *a)
{
	ft_skip_empty_lines(a);
	ft_printf("%s\n", a->file[a->i]);
	return (0);
}

int		ft_parsing(t_asm *a)
{
	ft_handle_comments(a->file);
	ft_get_name(a);
//	ft_get_comment(a);
	return (0);

}
