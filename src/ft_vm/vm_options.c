/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:11:44 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/20 16:44:22 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

/*
** To-do: Protect ft_atoi
*/

char	*g_options[OPT_NUM + 1] =
{
	"-d",
	"-s",
	"-v",
	"-b",
	"-n",
	"-a",
	0
};

int		vm_options(char **av, t_vm *v)
{
	int i;
	int j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (g_options[++j])
			if (ft_strequ(av[i], g_options[j]))
				v->opt[j] = 1;
		v->d_cy = (ft_strequ(av[i], "-d")) ? ft_atoi(av[i + 1]) : v->d_cy;
		v->s_cy = (ft_strequ(av[i], "-s")) ? ft_atoi(av[i + 1]) : v->s_cy;
		v->v_lvl = (ft_strequ(av[i], "-v")) ? ft_atoi(av[i + 1]) : v->v_lvl;
		if ((v->opt[OPT_D] && v->d_cy <= 0) ||
			(v->opt[OPT_S] && v->s_cy <= 0) ||
			(v->opt[OPT_V] && v->v_lvl <= 0))
			return (-1);
		if (ft_strequ(av[i], "-b") || ft_strequ(av[i], "-n"))
			v->stealth = ft_strequ(av[i + 1], "--stealth");
		if (((v->opt[OPT_D] || v->opt[OPT_S] || v->opt[OPT_V]) &&
			(v->opt[OPT_B] || v->opt[OPT_N])) ||
			(v->opt[OPT_B] && v->opt[OPT_N]))
			return (-1);
	}
//	i = -1;
//	while (++i < OPT_NUM)
//		ft_printf("%d: %d\n", i, v->opt[i]);
//	ft_printf("d_cy: %d s_cy: %d v_lvl: %d\n", v->d_cy, v->s_cy, v->v_lvl);
//	ft_printf("stealth: %d\n", v->stealth);
	return (0);
}
