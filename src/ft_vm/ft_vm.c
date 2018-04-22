/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:38:33 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/21 11:24:01 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

static int	vm_get_champions(char **av)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while (av[++i])
	{
		if (ft_strequ(&av[i][ft_strlen(av[i]) - 4], ".cor"))
			num++;
	}
	return (num);
}

static int	vm_print_usage(char **av, int status)
{
	ft_dprintf(2, "usage: %s [-dump nbr_cycles] [-n number] ", av[0]);
	ft_dprintf(2, "champion1.cor ...\n");
	return (status);
}

int			main(int ac, char **av)
{
	t_vm	v;

	ft_bzero(&v, sizeof(t_vm));
	if (ac < 2 || vm_options(av, &v) == -1)
		return (vm_print_usage(av, -1));
	else if (vm_get_champions(av) > MAX_PLAYERS)
	{
		ft_dprintf(2, "Too many champions\n");
		return (-1);
	}
	vm_print();
	return (0);
}
