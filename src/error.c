/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:48:12 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/15 11:59:44 by fpetras          ###   ########.fr       */
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
		ft_dprintf(2, "Malloc error 💥\n");
	if (errnum == HEADER)
		ft_dprintf(2, "Syntax Error - header\n");
	else if (errnum == NAME_LEN)
		ft_dprintf(2, "Error - maximum name length exceeded\n");
	else if (errnum == COMMENT_LEN)
		ft_dprintf(2, "Error - maximum comment length exceeded\n");
	else if (errnum == OP)
		ft_dprintf(2, "operation: Operation is invalid\n");
	return (status);
}
