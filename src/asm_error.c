/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:48:12 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/18 08:31:18 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

static void	ft_error_2(int errnum)
{
	if (errnum == OP_PARAM)
		ft_dprintf(2, "Error - Parameter is invalid\n");
	else if (errnum == LABEL_MISSING)
		ft_dprintf(2, "Error - Label is undefined\n");
	else if (errnum == OP_EMPTY)
		ft_dprintf(2, "Error - No operation found\n");
	else if (errnum == OP_PARAM_TYPE)
		ft_dprintf(2, "Error - Parameter type is invalid\n");
}

int			ft_error(int errnum, int status, char *line)
{
	if (line)
		ft_dprintf(2, "%*w%s%w\n", RED, line);
	if (errnum == NEWLINE)
	{
		ft_dprintf(2, "Syntax error - unexpected end of input ");
		ft_dprintf(2, "(Perhaps you forgot to end with a newline ?)\n");
	}
	if (errnum == EMPTY)
		ft_dprintf(2, "Error - File is empty\n");
	if (errnum == MALLOC)
		ft_dprintf(2, "Error - Malloc 💥\n");
	if (errnum == HEADER)
		ft_dprintf(2, "Syntax Error - Header\n");
	else if (errnum == NAME_LEN)
		ft_dprintf(2, "Error - Maximum name length exceeded\n");
	else if (errnum == COMMENT_LEN)
		ft_dprintf(2, "Error - Maximum comment length exceeded\n");
	else if (errnum == OP)
		ft_dprintf(2, "Error - Operation is invalid\n");
	else if (errnum == OP_NAME)
		ft_dprintf(2, "Error - Operation does not exist\n");
	else
		ft_error_2(errnum);
	return (status);
}
