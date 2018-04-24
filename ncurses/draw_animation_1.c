/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_animation_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 22:19:10 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/22 22:19:11 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/animation.h"

static void	draw_spark_1(WINDOW *w, int round)
{
	wattron(w, COLOR_PAIR(3));
	mvwprintw(w, 49, 10, "*");
	mvwprintw(w, 59, 5, "*");
	mvwprintw(w, 52, 50, "*");
	wattron(w, COLOR_PAIR(4));
	mvwprintw(w, 52, 40, "*");
	mvwprintw(w, 58, 55, "*");
	mvwprintw(w, 57, 22, "*");
	wattron(w, COLOR_PAIR(5));
	mvwprintw(w, 50, 22, "*");
	mvwprintw(w, 58, 17, "*");
	mvwprintw(w, 55, 35, "*");
	wattron(w, COLOR_PAIR(6));
	mvwprintw(w, 51, 13, "*");
	mvwprintw(w, 64, 20, "*");
	mvwprintw(w, 63, 54, "*");
	mvwprintw(w, 55, 4, "*");
}

static void	draw_spark_2(WINDOW *w, int round)
{
	wattron(w, COLOR_PAIR(3));
	mvwprintw(w, 48, 30, "*");
	mvwprintw(w, 58, 22, "*");
	mvwprintw(w, 51, 54, "*");
	wattron(w, COLOR_PAIR(4));
	mvwprintw(w, 50, 25, "*");
	mvwprintw(w, 56, 37, "*");
	mvwprintw(w, 59, 49, "*");
	wattron(w, COLOR_PAIR(5));
	mvwprintw(w, 54, 19, "*");
	mvwprintw(w, 59, 3, "*");
	mvwprintw(w, 61, 54, "*");
	wattron(w, COLOR_PAIR(6));
	mvwprintw(w, 50, 10, "*");
	mvwprintw(w, 61, 35, "*");
	mvwprintw(w, 55, 52, "*");
	mvwprintw(w, 53, 7, "*");
}

void		draw_animation(WINDOW *w, int cycle)
{
	int	round;

	round = cycle % 100;
	draw_guitar_1(w, round);
	draw_guitar_2(w, round);
	draw_drummer(w, round);
	draw_singer(w, round);
	draw_bass(w, round);
	round = cycle % 50;
	if (round < 20)
		draw_spark_1(w, round);
	else
		draw_spark_2(w, round);
}
