/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 22:25:40 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/15 22:25:41 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/animation.h"

void	draw(t_win win, unsigned char *memory, t_status *status)
{
	werase(win.game);
	werase(win.info);
	werase(win.nyan);
	draw_game(win, memory);
	draw_info(win, status);
	draw_nyan(win.nyan, (*status).cycle, &(*status).nyan_col);
	refresh();
	wrefresh(win.game);
	wrefresh(win.info);
	wrefresh(win.nyan);
}

int		main(int argc, char *argv[])
{
	time_t		start;
	t_status	status;
	t_win		win;
	unsigned char memory[MEM_SIZE];

	system("afplay -t 120 ~/Downloads/nyan.mp3&");
	ft_bzero(memory, MEM_SIZE);
	ft_bzero(&status, sizeof(t_status));
	init_ncurses();
	win.game = newwin(4 + (MEM_SIZE / 64), 197, 0 , 0);
	win.info = newwin(4 + (MEM_SIZE / 64), 58, 0, 196);
	win.nyan = newwin(9, 254, 4 + (MEM_SIZE / 64), 0);

	status.speed = 1;
	status.ctd_now = CYCLE_TO_DIE;
	start = time(NULL);
	while (status.ctd_now > 0)
	{
		if (time(NULL) - start >= 121)
		{
			system("afplay -t 120 ~/Downloads/nyan.mp3&");
			start = time(NULL);
		}
		status.delay = DELAY / status.speed;
		draw(win, memory, &status);
		if (status.pause == 0)
		{
			status.cycle++;
			status.c_now++;
		}
		if ((key_hook(&status)) == -1)
			break ;
		if (status.c_now > status.ctd_now)
		{
			status.ctd_now -= CYCLE_DELTA;
			status.c_now = 0;
		}
		usleep(status.delay);
	}
	draw_end(&win);
	return (0);
}



