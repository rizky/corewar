/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 05:04:15 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/26 10:58:30 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

static void	draw_map(WINDOW *win, unsigned char *memory)
{
	int i;
	int	col;
	int	row;

	i = 0;
	col = 0;
	row = 0;
	wattron(win, COLOR_PAIR(7));
	while (i < MEM_SIZE)
	{
		mvwprintw(win, (2 + row), 3 + (col * 3), "%02x ", memory[i]);
		i++;
		col++;
		if (col == 64)
		{
			col = 0;
			row++;
		}
	}
	wattroff(win, COLOR_PAIR(7));
}

void		draw_game(t_win win, unsigned char *memory)
{
	wattron(win.game, COLOR_PAIR(1));
	box(win.game, 'x', 'x');
	draw_map(win.game, memory);
	wattron(win.info, COLOR_PAIR(1));
	box(win.info, 'x', 'x');
}
