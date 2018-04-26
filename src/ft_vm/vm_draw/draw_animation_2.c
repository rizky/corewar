/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_animation_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 22:18:43 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/26 14:22:10 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

void	draw_guitar_1(WINDOW *w, int round)
{
	if (round < 40)
	{
		mvwprintw(w, 53, 9, "    ### ");
		mvwprintw(w, 54, 9, "   (' ')");
		mvwprintw(w, 55, 9, "  / ||/");
		mvwprintw(w, 56, 9, "=o=(=/)");
		mvwprintw(w, 57, 9, "   / |");
		mvwprintw(w, 58, 9, "  \"  \"");
	}
	else
	{
		mvwprintw(w, 53, 9, "   ### ");
		mvwprintw(w, 54, 9, "  (- -)");
		mvwprintw(w, 55, 9, " /  ||_\\");
		mvwprintw(w, 56, 9, "o==(==)");
		mvwprintw(w, 57, 9, "   / |");
		mvwprintw(w, 58, 9, "  \"  \"");
	}
}

void	draw_guitar_2(WINDOW *w, int round)
{
	if (round < 40)
	{
		mvwprintw(w, 53, 40, "   > < ");
		mvwprintw(w, 54, 40, "  (- -)");
		mvwprintw(w, 55, 40, " /  ||/");
		mvwprintw(w, 56, 40, "o==(=/)");
		mvwprintw(w, 57, 40, "   / |");
		mvwprintw(w, 58, 40, "  \"  \"");
	}
	else
	{
		mvwprintw(w, 53, 40, "    > < ");
		mvwprintw(w, 54, 40, "   (x x)");
		mvwprintw(w, 55, 40, "  / ||_\\");
		mvwprintw(w, 56, 40, "=o=(==)");
		mvwprintw(w, 57, 40, "   / |");
		mvwprintw(w, 58, 40, "  \"  \"");
	}
}

void	draw_drummer(WINDOW *w, int round)
{
	if (round < 40)
	{
		mvwprintw(w, 49, 20, "        ,,,");
		mvwprintw(w, 50, 20, "     \\ (* *)  /");
		mvwprintw(w, 51, 20, "  .----. ||\\/");
		mvwprintw(w, 52, 20, "//      \\\\' ");
		mvwprintw(w, 53, 20, "\\\\      //  [[ ]]");
		mvwprintw(w, 54, 20, "  '----'     ' '");
	}
	else
	{
		mvwprintw(w, 49, 20, "         ,,,");
		mvwprintw(w, 50, 20, "        (' ')  ");
		mvwprintw(w, 51, 20, "  .----. ||\\");
		mvwprintw(w, 52, 20, "/        \\' \\");
		mvwprintw(w, 53, 20, "\\        /   [ ]");
		mvwprintw(w, 54, 20, "  '----'     ' '");
	}
}

void	draw_singer(WINDOW *w, int round)
{
	if (round < 40)
	{
		mvwprintw(w, 56, 24, "    ~~~");
		mvwprintw(w, 57, 24, "   ('o')");
		mvwprintw(w, 58, 24, " /_o ||\\");
		mvwprintw(w, 59, 24, "  /  ''/");
		mvwprintw(w, 60, 24, " /   ||");
		mvwprintw(w, 61, 24, "'   \" \"");
	}
	else
	{
		mvwprintw(w, 56, 24, "     ~~~");
		mvwprintw(w, 57, 24, "    (' ')");
		mvwprintw(w, 58, 24, "o_/  ||\\");
		mvwprintw(w, 59, 24, "|    ''/");
		mvwprintw(w, 60, 24, "|   / |");
		mvwprintw(w, 61, 24, "'  \"  \"");
	}
}

void	draw_bass(WINDOW *w, int round)
{
	char x;

	if (round < 40)
		x = 'x';
	else
		x = 'X';
	mvwprintw(w, 59, 9, " -------");
	mvwprintw(w, 60, 8, "/      /|");
	mvwprintw(w, 61, 7, "-------  |");
	mvwprintw(w, 62, 7, "| %c%c%c |  |", x, x, x);
	mvwprintw(w, 63, 7, "| %c%c%c |  |", x, x, x);
	mvwprintw(w, 64, 7, "| %c%c%c | /", x, x, x);
	mvwprintw(w, 65, 6, " -------");
	mvwprintw(w, 59, 40, " -------");
	mvwprintw(w, 60, 41, "|\\      \\");
	mvwprintw(w, 61, 41, "|  -------");
	mvwprintw(w, 62, 41, "|  | %c%c%c |", x, x, x);
	mvwprintw(w, 63, 41, "|  | %c%c%c |", x, x, x);
	mvwprintw(w, 64, 41, " \\ | %c%c%c |", x, x, x);
	mvwprintw(w, 65, 43, " -------");
}
