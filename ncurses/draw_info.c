/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 04:54:09 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/24 04:54:10 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/animation.h"

static void	draw_main_info(t_win win, t_status *s)
{
	if ((*s).pause == 1)
	{
		wattron(win.info, COLOR_PAIR(5));
		mvwprintw(win.info, 2, 3, "** PAUSED **");
	}
	else
	{
		wattron(win.info, COLOR_PAIR(8));
		mvwprintw(win.info, 2, 3, "** PLAY **");
	}
	wattron(win.info, COLOR_PAIR(2));
	mvwprintw(win.info, 4, 3, "Cycles/second limit : %d", (*s).speed);
	mvwprintw(win.info, 7, 3, "* Total cycle : %d", (*s).cycle);
	mvwprintw(win.info, 9, 3, "* Processes : 2");
	wattron(win.info, COLOR_PAIR(4));
	mvwprintw(win.info, 11, 3, "* CYCLE_TO_DIE : %d / %d", (*s).c_now,
		(*s).ctd_now);
	wattron(win.info, COLOR_PAIR(6));
	mvwprintw(win.info, 17, 3, "* CYCLE_DELTA : %d", CYCLE_DELTA);
	wattron(win.info, COLOR_PAIR(5));
	mvwprintw(win.info, 19, 3, "* NBR_LIVE : %d	* MAX_CHECKS : %d",
		NBR_LIVE, MAX_CHECKS);
	wattron(win.info, COLOR_PAIR(2));
}

static void	draw_counter(t_win win, t_status *status, double *c_tmp)
{
	int		col;
	int		color;

	col = 0;
	color = 0;
	while (*c_tmp > 0)
	{
		if (col < 12)
			color = 11;
		else if (col >= 12 && col <= 24)
			color = 10;
		else
			color = 9;
		(*c_tmp)--;
		wattron(win.info, COLOR_PAIR(color));
		mvwprintw(win.info, 13, 5 + col, "-");
		wattroff(win.info, COLOR_PAIR(color));
		mvwprintw(win.info, 13, 6 + col, " ");
		col += 2;
	}
}

static void	draw_max_counter(t_win win, t_status *status, double *ctd_tmp)
{
	int		col;
	int		color;

	col = 0;
	color = 0;
	if (*ctd_tmp < 6)
		color = 11;
	else if (*ctd_tmp >= 6 && *ctd_tmp <= 13)
		color = 10;
	else
		color = 9;
	while (*ctd_tmp > 0)
	{
		wattron(win.info, COLOR_PAIR(color));
		mvwprintw(win.info, 15, 5 + col, "-");
		wattroff(win.info, COLOR_PAIR(color));
		mvwprintw(win.info, 15, 6 + col, " ");
		(*ctd_tmp)--;
		col += 2;
	}
}

void		draw_info(t_win win, t_status *status)
{
	double	c_tmp;
	double	ctd_tmp;

	c_tmp = ((double)(*status).c_now / (double)(*status).ctd_now * 20);
	ctd_tmp = ((double)(*status).ctd_now / (double)CYCLE_TO_DIE * 20);
	draw_main_info(win, status);
	draw_counter(win, status, &c_tmp);
	draw_max_counter(win, status, &ctd_tmp);
	draw_animation(win.info, (*status).cycle);
}
