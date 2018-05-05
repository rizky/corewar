/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 01:02:28 by jyeo              #+#    #+#             */
/*   Updated: 2018/05/04 20:17:18 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

static void	color_picker(int *i, int *color)
{
	if (*i + 1 == 1)
		*color = 13;
	else if (*i + 1 == 2)
		*color = 8;
	else if (*i + 1 == 3)
		*color = 3;
	else if (*i + 1 == 4)
		*color = 12;
	else
		*color = 7;
}

void		draw_player_info(t_vm *vm, t_win w)
{
	int			i;
	int			row;
	int			color;

	i = -1;
	row = 0;
	mvwprintw(w.info, 21, 3, "===============================================");
	mvwprintw(w.info, 21, 50, "=====");
	while (++i < vm->champ_size)
	{
		color_picker(&i, &color);
		wattron(w.info, COLOR_PAIR(7));
		mvwprintw(w.info, 23 + i + row, 3, "Player -%d : ", i + 1);
		mvwprintw(w.info, 24 + i + row, 3, "* Lives in current period :		%d",
			vm->champ[i].live_nbr);
		wattron(w.info, COLOR_PAIR(color));
		mvwprintw(w.info, 23 + i + row, 15, "%.38s",
			vm->champ[i].header.prog_name);
		(ft_strlen(vm->champ[i].header.prog_name) > 38) ?
			mvwprintw(w.info, 23 + i + row, 53, "...") : 0;
		wattroff(w.info, COLOR_PAIR(color));
		row += 3;
	}
}
