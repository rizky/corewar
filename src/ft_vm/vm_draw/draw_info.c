/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 04:54:09 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/26 14:22:29 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

static void	update_info(t_vm *vm, t_win win)
{
	int		live_nbr;
	int		process_nbr;

	live_nbr = vm_checker_livenbr(*vm);
	process_nbr = vm_checker_processnbr(*vm);
	mvwprintw(win.info, 9, 3, "* Processes : %d", process_nbr);
	wattron(win.info, COLOR_PAIR(5));
	mvwprintw(win.info, 19, 3, "* NBR_LIVE : %d/%d	* MAX_CHECKS : %d/%d",
		live_nbr, NBR_LIVE, vm->check_nbr, MAX_CHECKS);
}

static void	draw_main_info(t_vm *vm, t_win win, t_status *s)
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
	mvwprintw(win.info, 7, 3, "* Total cycle : %d", g_cycles);
	wattron(win.info, COLOR_PAIR(4));
	mvwprintw(win.info, 11, 3, "* CYCLE_TO_DIE : %d / %d", g_cycles_to,
		g_cycles_to_die);
	wattron(win.info, COLOR_PAIR(6));
	mvwprintw(win.info, 17, 3, "* CYCLE_DELTA : %d", CYCLE_DELTA);
	update_info(vm, win);
	wattron(win.info, COLOR_PAIR(2));
}

static void	draw_counter(t_win win, double *c_tmp)
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

static void	draw_max_counter(t_win win, double *ctd_tmp)
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

void		draw_info(t_vm *vm)
{
	double	c_tmp;
	double	ctd_tmp;

	c_tmp = ((double)g_cycles_to / (double)g_cycles_to_die * 20);
	ctd_tmp = ((double)g_cycles_to_die / (double)CYCLE_TO_DIE * 20);
	draw_main_info(vm, g_draw_win, &g_draw_status);
	draw_counter(g_draw_win, &c_tmp);
	draw_max_counter(g_draw_win, &ctd_tmp);
	draw_player_info(vm, g_draw_win);
	draw_animation(g_draw_win.info, g_cycles);
}
