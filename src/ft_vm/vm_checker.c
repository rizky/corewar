/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 12:15:39 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/25 12:24:50 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int
	vm_checker_livenbr(t_vm vm)
{
	int			i;
	int			j;
	int			live_nbr;
	t_process	*p;

	live_nbr = 0;
	i = -1;
	while (++i < vm.champ_size)
	{
		j = -1;
		while (++j < (int)(vm.champ[i].processes->size))
		{
			p = &(((t_process*)vm.champ[i].processes->data)[j]);
			live_nbr += p->live_nbr;
		}
	}
	return (live_nbr);
}
