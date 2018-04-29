/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 22:25:40 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/26 14:21:53 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

void	draw(t_vm *vm)
{
	//g_draw_status.delay = DELAY / g_draw_status.speed;
	werase(g_draw_win.game);
	werase(g_draw_win.info);
	werase(g_draw_win.nyan);
	draw_game(vm, g_draw_win);
	draw_info(vm);
	draw_nyan(g_draw_win.nyan, g_cycles, &g_draw_status.nyan_col);
	refresh();
	wrefresh(g_draw_win.game);
	wrefresh(g_draw_win.info);
	wrefresh(g_draw_win.nyan);
}

void	sighandle(int dummy)
{
	dummy = 0;
	g_signal = 0;
}

int		vm_start_ncurse(time_t *start, t_vm vm)
{
	int		key;

	(vm.v_lvl[V_LVL_1] && g_cycles == 1) ? init_ncurses(&vm, start) : 0;
	signal(SIGINT, sighandle);
	if (g_signal == 0)
		return (-1);
	while (g_draw_status.pause)
	{
		key = key_hook(&g_draw_status);
		draw(&vm);
		if (key == -1 || g_signal == 0)
			return (-1);
		else if (key == 1)
			return (0);
	}
	if (time(NULL) - *start >= 121)
	{
		system("afplay -t 120 sound/nyan.mp3&");
		*start = time(NULL);
	}
	draw(&vm);
	if ((key_hook(&g_draw_status)) == -1)
		return (-1);
	usleep(g_draw_status.delay);
	return (0);
}

