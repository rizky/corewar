/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 05:08:34 by jyeo              #+#    #+#             */
/*   Updated: 2018/05/04 20:17:30 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

void	draw_end(t_win *win)
{
	nodelay(stdscr, FALSE);
	mvwprintw((*win).info, 46, 15, "** PRESS ANY KEY TO EXIT **");
	wrefresh((*win).info);
	getch();
	system("if [ $(pgrep afplay) ]; \
		then kill $(pgrep afplay); fi");
	delwin((*win).game);
	delwin((*win).info);
	delwin((*win).nyan);
	endwin();
}
