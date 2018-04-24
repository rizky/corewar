/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 22:13:56 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/22 22:13:57 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H
# include <ncurses.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <time.h>
# include "op.h"
# include "../libft/includes/libft.h"

# define DELAY 1000000
# define COLOR_GREY 20
# define COLOR_BRIGHT_W 21
# define COLOR_BROWN_1 22
# define COLOR_PINK 23
# define COLOR_BLUE_L 24

typedef	struct	s_status
{
	int			pause;
	int			delay;
	int			speed;
	int 		cycle;
	int			c_now;
	int			ctd_now;
	int			nyan_col;
}				t_status;

typedef	struct	s_win
{
	WINDOW		*game;
	WINDOW		*info;
	WINDOW		*nyan;
}				t_win;

void		init_ncurses(void);
int 		key_hook(t_status *status);
void		draw_game(t_win win, unsigned char *memory);
void		draw_info(t_win win, t_status *status);
void		draw_animation(WINDOW *w, int cycle);
void		draw_guitar_1(WINDOW *w, int cycle);
void		draw_guitar_2(WINDOW *w, int cycle);
void		draw_drummer(WINDOW *w, int cycle);
void		draw_singer(WINDOW *w, int cycle);
void		draw_bass(WINDOW *w, int cycle);
void		draw_nyan(WINDOW *w, int cycle, int *nyan_col);
void		draw_end(t_win *win);

#endif
