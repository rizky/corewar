/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm_draw.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 22:13:56 by jyeo              #+#    #+#             */
/*   Updated: 2018/05/06 11:10:56 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VM_DRAW_H
# define FT_VM_DRAW_H

# include <ncurses.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <time.h>
# include "ft_vm.h"

# define DELAY 1000000
# define COLOR_GREY 20
# define COLOR_BRIGHT_W 21
# define COLOR_BROWN_1 22
# define COLOR_PINK 23
# define COLOR_BLUE_L 24
# define COLOR_BROWN_BG 25
# define COLOR_PINK_BG 26
# define COLOR_GREEN_BG 27
# define COLOR_BLUE_BG 28

# define ESC 27
# define SPACE 32

typedef	struct	s_status
{
	int			pause;
	int			delay;
	int			speed;
	int			nyan_col;
	int			process;
}				t_status;

typedef	struct	s_win
{
	WINDOW		*game;
	WINDOW		*info;
	WINDOW		*nyan;
}				t_win;

t_status		g_draw_status;
t_win			g_draw_win;
int				g_signal;

void			init_ncurses(t_vm *vm, time_t *start);
int				vm_start_ncurses(time_t *start, t_vm vm);
void			draw_info(t_vm *vm);
void			draw_player_info(t_vm *vm, t_win win);
void			draw_game(t_vm *v, t_win w);

void			draw_animation(WINDOW *w, int cycle);
void			draw_guitar_1(WINDOW *w, int cycle);
void			draw_guitar_2(WINDOW *w, int cycle);
void			draw_drummer(WINDOW *w, int cycle);
void			draw_singer(WINDOW *w, int cycle);
void			draw_bass(WINDOW *w, int cycle);
void			draw_nyan(WINDOW *w, int cycle, int *nyan_col);
void			draw_end(t_win *win);

int				key_hook(t_status *status);

#endif
