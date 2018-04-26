/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 22:25:40 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/26 13:18:58 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	draw(t_vm *vm)
{
	g_draw_status.delay = DELAY / g_draw_status.speed;
	werase(g_draw_win.game);
	werase(g_draw_win.info);
	werase(g_draw_win.nyan);
	draw_game(g_draw_win, g_memory);
	draw_info(vm);
	draw_nyan(g_draw_win.nyan, g_cycles, &g_draw_status.nyan_col);
	refresh();
	wrefresh(g_draw_win.game);
	wrefresh(g_draw_win.info);
	wrefresh(g_draw_win.nyan);
	if (g_draw_status.pause == 0)
		g_draw_status.c_now++;
	if (g_draw_status.c_now > g_cycles_to_die)
		g_draw_status.c_now = 0;
}

int		start_ncurses(int start, t_vm vm)
{
	while (g_draw_status.pause)
		;
	if (time(NULL) - start >= 121)
	{
//		system("afplay -t 120 sound/nyan.mp3&");
		start = time(NULL);
	}
	draw(&vm);
	if ((key_hook(&g_draw_status)) == -1)
		return (-1);
	usleep(g_draw_status.delay);
	return (0);
}

// int		main(int argc, char *argv[])
// {
// 	time_t		start;
// 	t_status	status;
// 	t_win		win;
// 	unsigned char memory[MEM_SIZE];

// 	system("afplay -t 120 ~/Downloads/nyan.mp3&");
// 	ft_bzero(memory, MEM_SIZE);
// 	ft_bzero(&status, sizeof(t_status));
// 	init_ncurses();
// 	win.game = newwin(4 + (MEM_SIZE / 64), 197, 0 , 0);
// 	win.info = newwin(4 + (MEM_SIZE / 64), 58, 0, 196);
// 	win.nyan = newwin(9, 254, 4 + (MEM_SIZE / 64), 0);

// 	status.speed = 1;
// 	status.ctd_now = CYCLE_TO_DIE;
// 	start = time(NULL);
// 	while (status.ctd_now > 0)
// 	{
// 		if (time(NULL) - start >= 121)
// 		{
// 			system("afplay -t 120 ~/Downloads/nyan.mp3&");
// 			start = time(NULL);
// 		}
// 		status.delay = DELAY / status.speed;
// 		draw(win, memory, &status);
// 		if (status.pause == 0)
// 		{
// 			status.cycle++;
// 			status.c_now++;
// 		}
// 		if ((key_hook(&status)) == -1)
// 			break ;
// 		if (status.c_now > status.ctd_now)
// 		{
// 			status.ctd_now -= CYCLE_DELTA;
// 			status.c_now = 0;
// 		}
// 		usleep(status.delay);
// 	}
// 	draw_end(&win);
// 	return (0);
// }
