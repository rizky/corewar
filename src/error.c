/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:48:12 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/14 15:02:46 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_error(int errnum, int status)
{
	if (errnum == NEWLINE)
	{
		ft_dprintf(2, "Syntax error - unexpected end of input ");
		ft_dprintf(2, "(Perhaps you forgot to end with a newline ?)\n");
	}
	if (errnum == EMPTY)
		ft_dprintf(2, "Empty file\n");
	if (errnum == MALLOC)
		ft_dprintf(2, "Malloc error\n");
	if (errnum == NAME)
		ft_dprintf(2, ".name: Syntax Error\n");
	else if (errnum == NAME_LEN)
		ft_dprintf(2, ".name: Name too long\n");
	else if (errnum == COMMENT)
		ft_dprintf(2, ".comment: Syntax Error\n");
	else if (errnum == COMMENT_LEN)
		ft_dprintf(2, ".comment: Comment too long\n");
	else if (errnum == OP)
		ft_dprintf(2, "operation: Operation is invalid\n");
	return (status);
}
