/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 22:25:40 by jyeo              #+#    #+#             */
/*   Updated: 2018/05/01 10:19:02 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

static void	vm_signal(int sig)
{
	(void)sig;
	system("pkill afplay 2>&-");
	endwin();
	exit(0);
}

void		draw(t_vm *vm)
{
	signal(SIGINT, vm_signal);
	g_draw_status.delay = DELAY / g_draw_status.speed;
	werase(g_draw_win.game);
	werase(g_draw_win.info);
	werase(g_draw_win.nyan);
	draw_game(vm, g_draw_win, g_memory, g_memory_mark);
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
