/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_helper_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:58:02 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/22 22:12:50 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int
	vm_getoptions(char **av, int opt[OPT_NUM])
{
	int			i;
	int			j;
	int			k;
	int			c;

	c = 0;
	i = 0;
	while (av[++i] && av[i][0] == '-')
	{
		j = 0;
		k = 0;
		while (av[i][++j])
			if ((c = is_in(av[i][j], OPT_STR_V)) != -1)
			{
				i = (!av[i + k + 1] || ft_atoi(av[i + k + 1]) == 0) ? -1 : 0;
				opt[c] = ft_atoi(av[i + ++k]);
			}
			else if ((c = is_in(av[i][j], OPT_STR)) != -1)
				opt[c] = 1;
			else
				return (i);
		i += k;
	}
	return (i);
}
