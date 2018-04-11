/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:48:12 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/11 14:51:09 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_error(int errnum, int status)
{
	if (errnum == NAME)
		ft_dprintf(2, ".name: Syntax Error\n");
	else if (errnum == COMMENT)
		ft_dprintf(2, ".comment: Syntax Error\n");
	return (status);
}
