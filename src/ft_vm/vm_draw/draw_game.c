/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 05:04:15 by jyeo              #+#    #+#             */
/*   Updated: 2018/05/04 20:16:41 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

static void	process_color(t_process *p, unsigned char *m, int *i, int *col)
{
	if (p->pc + p->offset == *i)
	{
		if (m[*i] == 1)
		{
			if (p->champ == 0)
				*col = 18;
			else if (p->champ == 1)
				*col = 19;
			else if (p->champ == 2)
				*col = 20;
			else if (p->champ == 3)
				*col = 21;
		}
		else if (m[*i] == 2)
		{
			if (p->champ == 0)
				*col = 22;
			else if (p->champ == 1)
				*col = 23;
			else if (p->champ == 2)
				*col = 24;
			else if (p->champ == 3)
				*col = 25;
		}
		else if (m[*i] == 3)
		{
			if (p->champ == 0)
				*col = 26;
			else if (p->champ == 1)
				*col = 27;
			else if (p->champ == 2)
				*col = 28;
			else if (p->champ == 3)
				*col = 29;
		}
		else if (m[*i] == 4)
		{
			if (p->champ == 0)
				*col = 30;
			else if (p->champ == 1)
				*col = 31;
			else if (p->champ == 2)
				*col = 32;
			else if (p->champ == 3)
				*col = 33;
		}
		else
		{
			if (p->champ == 0)
				*col = 14;
			else if (p->champ == 1)
				*col = 15;
			else if (p->champ == 2)
				*col = 16;
			else if (p->champ == 3)
				*col = 17;
		}
	}
}

static void	color_picker(t_vm *vm, unsigned char *m, int *i, int *color)
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
	while (++y < (int)vm->processes.size)
	{
		p = &(((t_process*)vm->processes.data)[y]);
		process_color(p, m, i, color);
	}
}

static void	draw_map(t_vm *v, t_win w)
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

void		draw_game(t_vm *v, t_win w)
{
	wattron(w.game, COLOR_PAIR(1));
	box(w.game, 'x', 'x');
	draw_map(v, w);
	wattron(w.info, COLOR_PAIR(1));
	box(w.info, 'x', 'x');
}
