/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 05:08:34 by jyeo              #+#    #+#             */
/*   Updated: 2018/05/06 10:09:19 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

void	draw_end(t_win *win)
{
	nodelay(stdscr, FALSE);
	mvwprintw((*win).info, 46, 15, "** PRESS ANY KEY TO EXIT **");
	wrefresh((*win).info);
	system("if [ $(pgrep afplay) ]; \
		then kill $(pgrep afplay); fi");
	if (system("test -r resources/sound/win.wav") == 0)
		system("afplay resources/sound/win.wav&");
	getch();
	system("if [ $(pgrep afplay) ]; \
		then kill $(pgrep afplay); fi");
	delwin((*win).game);
	delwin((*win).info);
	delwin((*win).nyan);
	endwin();
}
