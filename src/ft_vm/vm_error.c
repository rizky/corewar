/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:00:18 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/06 08:56:10 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int			vm_error(int errnum, int status, char *name)
{
	if (name)
		ft_dprintf(2, "%*w%s%w\n", RED, name);
	if (errnum == MALLOC)
		write(2, "Error - Malloc 💥\n", 20);
	else if (errnum == CHAMP_MIN)
		ft_dprintf(2, "Error - Minimum number of players is 1\n");
	else if (errnum == CHAMP_MAX)
		ft_dprintf(2, "Error - Maximum number of players is %d\n", MAX_PLAYERS);
	else if (errnum == INVALID_FILE && name)
		ft_dprintf(2, "Error - File is invalid\n");
	else if (errnum == INVALID_FILE)
		ft_dprintf(2, "Error - Missing player\n");
	else if (errnum == INVALID_HEADER)
		ft_dprintf(2, "Error - Header is invalid\n");
	else if (errnum == INVALID_MAGIC)
		ft_dprintf(2, "Error - Invalid file signature\n");
	else if (errnum == INVALID_INSTR)
		ft_dprintf(2, "Error - Inconsistent number of instructions\n");
	else if (errnum == CODE_MAX)
		ft_dprintf(2, "Error - Code is too large (max %d bytes) \n",
			CHAMP_MAX_SIZE);
	else if (errnum == NO_CODE)
		ft_dprintf(2, "Error - No code found in the file\n");
	return (status);
}
