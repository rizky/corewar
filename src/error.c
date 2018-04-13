/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:48:12 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/13 17:26:10 by rnugroho         ###   ########.fr       */
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
	else if (errnum == OP)
		ft_dprintf(2, "operation: Operation is invalid\n");
	return (status);
}
