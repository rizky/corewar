/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_nyan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 03:59:07 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/26 13:08:15 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

static void	draw_nyan_2(WINDOW *w, int *nyan_col)
{
	wattron(w, COLOR_PAIR(3));
	mvwprintw(w, 0, 2 + *nyan_col, "   +    +   o  ");
	wattron(w, COLOR_PAIR(13));
	mvwprintw(w, 1, 2 + *nyan_col, " o    +        +");
	wattron(w, COLOR_PAIR(2));
	mvwprintw(w, 2, 2 + *nyan_col, " ,- - - - -,");
	mvwprintw(w, 3, 2 + *nyan_col, " |         |");
	mvwprintw(w, 4, 2 + *nyan_col, " |      ^   ^");
	mvwprintw(w, 5, 2 + *nyan_col, "\\|_ _ _( ^ .^)");
	mvwprintw(w, 6, 2 + *nyan_col, "    \"\"   \"\"");
	wattron(w, COLOR_PAIR(3));
	mvwprintw(w, 7, 2 + *nyan_col, "    o        + ");
	wattron(w, COLOR_PAIR(13));
	mvwprintw(w, 8, 2 + *nyan_col, "  o    +    o ");
}

static void	draw_nyan_1(WINDOW *w, int *nyan_col)
{
	wattron(w, COLOR_PAIR(13));
	mvwprintw(w, 0, 2 + *nyan_col, "   +    o   + ");
	wattron(w, COLOR_PAIR(3));
	mvwprintw(w, 1, 2 + *nyan_col, " +        +   ");
	wattron(w, COLOR_PAIR(2));
	mvwprintw(w, 2, 2 + *nyan_col, " ,- - - - -,");
	mvwprintw(w, 3, 2 + *nyan_col, " |         |");
	mvwprintw(w, 4, 2 + *nyan_col, " |      ^   ^");
	mvwprintw(w, 5, 2 + *nyan_col, "~|_ _ _( ^ .^)");
	mvwprintw(w, 6, 2 + *nyan_col, "  \"\"   \"\" ");
	wattron(w, COLOR_PAIR(13));
	mvwprintw(w, 7, 2 + *nyan_col, "     +     + ");
	wattron(w, COLOR_PAIR(3));
	mvwprintw(w, 8, 2 + *nyan_col, " +       o    ");
}

static void	draw_nyan_path_2(WINDOW *w, int col)
{
	wattron(w, COLOR_PAIR(13));
	mvwprintw(w, 0, col, "  o  ");
	wattron(w, COLOR_PAIR(3));
	mvwprintw(w, 1, col, " +   ");
	wattron(w, COLOR_PAIR(5));
	mvwprintw(w, 2, col, "- - -");
	wattron(w, COLOR_PAIR(4));
	mvwprintw(w, 3, col, " _ _ ");
	wattron(w, COLOR_PAIR(8));
	mvwprintw(w, 4, col, "- - -");
	wattron(w, COLOR_PAIR(12));
	mvwprintw(w, 5, col, " _ _ ");
	wattron(w, COLOR_PAIR(13));
	mvwprintw(w, 6, col, "   + ");
	wattron(w, COLOR_PAIR(3));
	mvwprintw(w, 7, col, " +   ");
	wattron(w, COLOR_PAIR(13));
	mvwprintw(w, 8, col, "  o  ");
}

static void	draw_nyan_path_1(WINDOW *w, int col)
{
	wattron(w, COLOR_PAIR(3));
	mvwprintw(w, 0, col, " +   ");
	wattron(w, COLOR_PAIR(13));
	mvwprintw(w, 1, col, "   o ");
	wattron(w, COLOR_PAIR(5));
	mvwprintw(w, 2, col, " _ _ ");
	wattron(w, COLOR_PAIR(4));
	mvwprintw(w, 3, col, "- - -");
	wattron(w, COLOR_PAIR(8));
	mvwprintw(w, 4, col, " _ _ ");
	wattron(w, COLOR_PAIR(12));
	mvwprintw(w, 5, col, "- - -");
	wattron(w, COLOR_PAIR(3));
	mvwprintw(w, 6, col, "  +  ");
	wattron(w, COLOR_PAIR(13));
	mvwprintw(w, 7, col, "o    ");
	wattron(w, COLOR_PAIR(3));
	mvwprintw(w, 8, col, "   + ");
}

void		draw_nyan(WINDOW *w, int cycle, int *nyan_col)
{
	int		col;
	int		round;

	if (*nyan_col > 235)
		*nyan_col = 0;
	round = cycle % 100;
	col = *nyan_col;
	while (col > 0)
	{
		if (col % 2 == 0)
			draw_nyan_path_1(w, col);
		else
			draw_nyan_path_2(w, col);
		col -= 5;
	}
	if (round < 40)
		draw_nyan_1(w, nyan_col);
	else
		draw_nyan_2(w, nyan_col);
	if (round == 0)
		(*nyan_col)++;
}
