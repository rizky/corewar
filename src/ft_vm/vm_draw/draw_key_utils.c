/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_key_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 05:01:43 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/26 10:58:39 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm_draw.h"

static void	key_speed(int ch, t_status *status)
{
	if (ch == KEY_RIGHT)
		(*status).speed += 10;
	if (ch == KEY_UP)
		(*status).speed += 1;
	if (ch == KEY_LEFT)
		(*status).speed -= 10;
	if (ch == KEY_DOWN)
		(*status).speed -= 1;
	if ((*status).speed > 1000)
		(*status).speed = 1000;
	if ((*status).speed < 1)
		(*status).speed = 1;
}

int			key_hook(t_status *status)
{
	int		ch;

	ch = getch();
	if (ch == 32)
	{
		if ((*status).pause == 0)
		{
			system("kill -STOP $(pgrep afplay)");
			(*status).pause = 1;
		}
		else if ((*status).pause == 1)
		{
			system("kill -CONT $(pgrep afplay)");
			(*status).pause = 0;
		}
	}
	if (ch == 27)
		return (-1);
	key_speed(ch, status);
	return (0);
}
