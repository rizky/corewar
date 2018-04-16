/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helper_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:11:09 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/16 10:47:27 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

void	ft_print_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

int		ft_free_asm(t_asm *a, int status)
{
	fta_clear(a->ops);
	ft_free_tab(a->file, status);
	return (status);
}

int		ft_free_tab(char **tab, int status)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (status);
}

int		ft_free(char *str, int status)
{
	free(str);
	return (status);
}

int		asm_getoptions(char **av, int opt[OPT_NUM])
{
	int			i;
	int			j;
	const char	*c_opt = "am";
	int			c;

	c = 0;
	ft_bzero(opt, 2 * sizeof(int));
	i = 0;
	while (av[++i] && av[i][0] == '-')
	{
		j = 0;
		while (av[i][++j])
			if ((c = is_in(av[i][j], c_opt)) != -1)
				opt[c] = 1;
			else
				return (i);
	}
	return (i);
}