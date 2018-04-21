/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:11:44 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/20 07:34:11 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

/*
** To-do: Protect ft_atoi
*/

int		vm_options(char **av, t_vm *v)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while (av[++i])
	{
		if (!ft_strcmp(av[i], "-dump"))
		{
			v->dump = 1;
			if ((v->cycles = ft_atoi(av[i + 1])) <= 0)
					return (-1);
		}
		else if (!ft_strcmp(av[i], "-n"))
		{
			num = ft_atoi(av[i + 1]);
			if (num < 1 || num > MAX_PLAYERS)
				return (-1);
			if (av[i + 2] &&
				!ft_strequ(&av[i + 2][ft_strlen(av[i + 2]) - 4], ".cor"))
				return (-1);
			v->players[num] = av[i + 2];
		}
		else if (!ft_strncmp(av[i], "-n", 2))
		{
			num = ft_atoi(&av[i][2]);
			if (num < 1 || num > MAX_PLAYERS)
				return (-1);
			if (av[i + 1] &&
				!ft_strequ(&av[i + 1][ft_strlen(av[i + 1]) - 4], ".cor"))
				return (-1);
			v->players[num] = av[i + 1];
		}
	}
	ft_printf("dump: %d cycles: %d\n", v->dump, v->cycles);
	i = -1;
	while (++i < MAX_PLAYERS)
	ft_printf("%s\n", v->players[i]);
	return (0);
}
