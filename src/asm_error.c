/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:48:12 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/15 13:03:16 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int		ft_error(int errnum, int status, char *line)
{
	if (line)
		ft_dprintf(2, "%s\n", line);
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
		ft_dprintf(2, "Operation: Operation is invalid\n");
	else if (errnum == LABEL_MISSING)
		ft_dprintf(2, "Label: Undefined Label\n");
	return (status);
}
