/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 05:04:15 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/26 14:22:23 by fpetras          ###   ########.fr       */
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
	int			x;
	int			y;
	t_process	*p;

	x = vm->champ_size - 1;
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
	while (x >= 0)
	{
		y = -1;
		while (++y < (int)vm->champ[x].processes->size)
		{
			p = &(((t_process*)vm->champ[x].processes->data)[y]);
			process_color(p, m, i, color);
		}
		x--;
	}
}

static void		draw_map(t_vm *v, t_win w, unsigned char *m1, unsigned char *m2)
{
	int			i;
	int			col;
	int			row;
	int			color;
	// unsigned char	m[MEM_SIZE];

	i = 0;
	col = 0;
	row = 0;
	color = 7;
	// ft_memcpy(m, m1, MEM_SIZE);
	// ft_bzero(m, MEM_SIZE);
	while (i < MEM_SIZE)
	{
		// if (g_cylcm[i] != m1[i])
		// {
			color_picker(v, m2, &i, &color);
			wattron(w.game, COLOR_PAIR(color));
			mvwprintw(w.game, (2 + row), 3 + (col * 3), "%02x", m1[i]);
			// m[i] = m1[i];
		// }
		col++;
		i++;
		if (col == 64)
		{
			col = 0;
			row++;
		}
		// ft_memcpy(m, m1, MEM_SIZE);
	}
	wattroff(w.game, COLOR_PAIR(7));
}

void			draw_game(t_vm *v, t_win w, unsigned char *m, unsigned char *m2)
{
	wattron(w.game, COLOR_PAIR(1));
	box(w.game, 'x', 'x');
	draw_map(v, w, m, m2);
	wattron(w.info, COLOR_PAIR(1));
	box(w.info, 'x', 'x');
}
