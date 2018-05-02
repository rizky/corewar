/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 05:04:15 by jyeo              #+#    #+#             */
/*   Updated: 2018/05/02 15:57:09 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

static void		process_color(t_process *p, unsigned char *m, int *i, int *col)
{
	if (p->pc + p->offset == *i)
	{
		if (m[*i] == 1)
			*col = 14;
		else if (m[*i] == 2)
			*col = 15;
		else if (m[*i] == 3)
			*col = 16;
		else if (m[*i] == 4)
			*col = 17;
		else
			*col = 1;
	}
}

static void		color_picker(t_vm *vm, unsigned char *m, int *i, int *color)
{
	int			y;
	t_process	*p;

	if (m[*i] == 1)
		*color = 13;
	else if (m[*i] == 2)
		*color = 8;
	else if (m[*i] == 3)
		*color = 3;
	else if (m[*i] == 4)
		*color = 12;
	else
		*color = 7;
	y = -1;
	while (++y < (int)vm->processes->size)
	{
		p = &(((t_process*)vm->processes->data)[y]);
		process_color(p, m, i, color);
	}
}

static void		draw_map(t_vm *v, t_win w)
{
	int			i;
	int			col;
	int			row;
	int			color;

	i = 0;
	col = 0;
	row = 0;
	color = 7;
	while (i < MEM_SIZE)
	{
		color_picker(v, g_memory_mark, &i, &color);
		wattron(w.game, COLOR_PAIR(color));
		mvwprintw(w.game, (2 + row), 3 + (col * 3), "%02x", g_memory[i]);
		col++;
		i++;
		if (col == 64)
		{
			col = 0;
			row++;
		}
	}
	wattroff(w.game, COLOR_PAIR(7));
}

void			draw_game(t_vm *v, t_win w)
{
	wattron(w.game, COLOR_PAIR(1));
	box(w.game, 'x', 'x');
	draw_map(v, w);
	wattron(w.info, COLOR_PAIR(1));
	box(w.info, 'x', 'x');
}
