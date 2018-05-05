/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:28:14 by fpetras           #+#    #+#             */
/*   Updated: 2018/05/04 21:51:40 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"
#include "ft_vm_draw.h"

void	vm_free(t_vm *vm)
{
	int i;

	(vm->option_g[VISU_2]) ? draw_end(&g_draw_win) : 0;
	i = 0;
	while (i < vm->champ_size)
	{
		free(vm->champ[i].op);
		fta_clear(&(vm->processes));
		i++;
	}
}

int		vm_free_err(t_vm *vm, int max, int errnum, char *file)
{
	int i;

	i = 0;
	while (i < max)
	{
		free(vm->champ[i].op);
		fta_clear(&(vm->processes));
		i++;
	}
	return (vm_error(errnum, -1, (errnum == MALLOC) ? NULL : file));
}
