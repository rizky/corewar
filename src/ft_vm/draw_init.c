/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 05:00:22 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/24 05:00:24 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

static void	init_all_color(void)
{
	init_color(COLOR_GREY, 350, 350, 350);
	init_color(COLOR_BRIGHT_W, 1000, 1000, 1000);
	init_color(COLOR_BROWN_1, 920, 790, 0);
	init_color(COLOR_PINK, 1000, 412, 706);
	init_color(COLOR_BLUE_L, 0, 1000, 1000);
	init_pair(1, COLOR_GREY, COLOR_GREY);
	init_pair(2, COLOR_BRIGHT_W, COLOR_BLACK);
	init_pair(3, COLOR_BROWN_1, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_GREY, COLOR_BLACK);
	init_pair(8, COLOR_GREEN, COLOR_BLACK);
	init_pair(9, COLOR_GREEN, COLOR_GREEN);
	init_pair(10, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(11, COLOR_RED, COLOR_RED);
	init_pair(12, COLOR_PINK, COLOR_BLACK);
	init_pair(13, COLOR_BLUE_L, COLOR_BLACK);
}

void		init_ncurses(t_vm *vm)
{
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	start_color();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	init_all_color();
	(*vm).win.game = newwin(4 + (MEM_SIZE / 64), 197, 0 , 0);
	(*vm).win.info = newwin(4 + (MEM_SIZE / 64), 58, 0, 196);
	(*vm).win.nyan = newwin(9, 254, 4 + (MEM_SIZE / 64), 0);
	(*vm).status.speed = 1;
	system("afplay -t 120 sound/nyan.mp3&");
	// (*vm).status.ctd_now = CYCLE_TO_DIE;
}
