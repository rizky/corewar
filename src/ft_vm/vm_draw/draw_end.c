/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 05:08:34 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/26 10:58:27 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

void	draw_end(t_win *win)
{
	nodelay(stdscr, FALSE);
	mvwprintw((*win).info, 46, 15, "** PRESS ANY KEY TO EXIT **");
	wrefresh((*win).info);
	getch();
	system("kill $(pgrep afplay)");
	delwin((*win).game);
	delwin((*win).info);
	delwin((*win).nyan);
	endwin();
}
