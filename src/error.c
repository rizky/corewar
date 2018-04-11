/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:48:12 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/11 15:18:16 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_error(int errnum, int status)
{
	if (errnum == NAME)
		ft_dprintf(2, ".name: Syntax Error\n");
	else if (errnum == NAME_LEN)
		ft_dprintf(2, ".name: Name too long\n");
	else if (errnum == COMMENT)
		ft_dprintf(2, ".comment: Syntax Error\n");
	else if (errnum == COMMENT_LEN)
		ft_dprintf(2, ".comment: Comment too long\n");
	return (status);
}
