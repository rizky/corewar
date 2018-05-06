/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 05:00:22 by jyeo              #+#    #+#             */
/*   Updated: 2018/05/04 20:30:47 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

static void	init_all_color_2(void)
{
	init_pair(14, COLOR_GREY, COLOR_BLUE_BG);
	init_pair(15, COLOR_GREY, COLOR_GREEN_BG);
	init_pair(16, COLOR_GREY, COLOR_BROWN_BG);
	init_pair(17, COLOR_GREY, COLOR_PINK_BG);
	init_pair(18, COLOR_BLUE_L, COLOR_BLUE_BG);
	init_pair(19, COLOR_BLUE_L, COLOR_GREEN_BG);
	init_pair(20, COLOR_BLUE_L, COLOR_BROWN_BG);
	init_pair(21, COLOR_BLUE_L, COLOR_PINK_BG);
	init_pair(22, COLOR_GREEN, COLOR_BLUE_BG);
	init_pair(23, COLOR_GREEN, COLOR_GREEN_BG);
	init_pair(24, COLOR_GREEN, COLOR_BROWN_BG);
	init_pair(25, COLOR_GREEN, COLOR_PINK_BG);
	init_pair(26, COLOR_BROWN_1, COLOR_BLUE_BG);
	init_pair(27, COLOR_BROWN_1, COLOR_GREEN_BG);
	init_pair(28, COLOR_BROWN_1, COLOR_BROWN_BG);
	init_pair(29, COLOR_BROWN_1, COLOR_PINK_BG);
	init_pair(30, COLOR_PINK, COLOR_BLUE_BG);
	init_pair(31, COLOR_PINK, COLOR_GREEN_BG);
	init_pair(32, COLOR_PINK, COLOR_BROWN_BG);
	init_pair(33, COLOR_PINK, COLOR_PINK_BG);
}

static void	init_all_color(void)
{
	init_color(COLOR_GREY, 350, 350, 350);
	init_color(COLOR_BRIGHT_W, 1000, 1000, 1000);
	init_color(COLOR_BROWN_1, 920, 790, 0);
	init_color(COLOR_PINK, 1000, 412, 706);
	init_color(COLOR_BLUE_L, 0, 1000, 1000);
	init_color(COLOR_BROWN_BG, 368, 316, 0);
	init_color(COLOR_PINK_BG, 400, 164, 282);
	init_color(COLOR_GREEN_BG, 0, 400, 26);
	init_color(COLOR_BLUE_BG, 0, 400, 400);
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
	init_all_color_2();
}

void		init_ncurses(t_vm *vm, time_t *start)
{
	(void)*vm;
	*start = time(NULL);
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	start_color();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	init_all_color();
	ft_bzero(&g_draw_status, sizeof(g_draw_status));
	if (system("test -r resources/sound/nyan.mp3") == 0)
		system("afplay -t 120 resources/sound/nyan.mp3&");
	g_draw_win.game = newwin(4 + (MEM_SIZE / 64), 197, 0, 0);
	g_draw_win.info = newwin(4 + (MEM_SIZE / 64), 58, 0, 196);
	g_draw_win.nyan = newwin(9, 254, 4 + (MEM_SIZE / 64), 0);
	g_draw_status.speed = 50;
	g_draw_status.pause = 1;
	g_draw_status.process = vm->processes.size;
	g_signal = 1;
}
