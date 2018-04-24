/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 06:21:14 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/22 06:21:16 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hash(const char **str, char **flag, t_width *w)
{
	if (((**str) == 'o' || (**str) == 'O'))
	{
		*flag = "0";
		(*w).precision -= 1;
	}
	else if ((**str) == 'x')
	{
		*flag = "0x";
		(*w).width = (*w).width - 1;
	}
	else if ((**str) == 'X')
	{
		*flag = "0X";
		(*w).width = (*w).width - 1;
	}
	else
		*flag = NULL;
	return (0);
}

int			ft_flag_hash(const char **str, char **flag, char **s, t_width *w)
{
	if (*flag)
	{
		if (ft_strcmp(*flag, "#") == 0 && ft_strcmp(*s, "0") != 0)
			ft_hash(str, flag, w);
		else if (ft_strcmp(*flag, "#") == 0 && (*w).precision == 0
			&& ((**str) == 'o' || (**str) == 'O'))
			*flag = "0";
		else if (ft_strcmp(*flag, "+") != 0 && ft_strcmp(*flag, " ") != 0)
			*flag = NULL;
	}
	return (0);
}
