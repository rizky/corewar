/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 21:15:18 by rnugroho          #+#    #+#             */
/*   Updated: 2018/02/20 19:33:08 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wchar.h"

size_t		ft_wstrlen(const wchar_t *wstr)
{
	const wchar_t	*ptr = wstr;

	while (*ptr)
		ptr++;
	return (ptr - wstr);
}

/*
** https://www.cprogramming.com/tutorial/unicode.html
*/

size_t		ft_widetoa_(char *buff, wint_t w)
{
	if (w < 0)
	{
		*buff = w;
		return (1);
	}
	else if (w < 0x80)
	{
		*buff = (w & 0x7f);
		return (1);
	}
	else if (w < 0x800)
	{
		*(buff++) = ((w >> 6) & 0x1F) | 0xC0;
		*buff = ((w >> 0) & 0x3F) | 0x80;
		return (2);
	}
	else
		return (0);
}

size_t		ft_widetoa(char *buff, wint_t w)
{
	int		result;

	result = ft_widetoa_(buff, w);
	if (result != 0)
		return (result);
	else if (w < 0x10000)
	{
		*(buff++) = ((w >> 12) & 0xF) | 0xE0;
		*(buff++) = ((w >> 6) & 0x3F) | 0x80;
		*buff = ((w >> 0) & 0x3F) | 0x80;
		return (3);
	}
	else if (w < 0x110000)
	{
		*(buff++) = ((w >> 18) & 0x7) | 0xF0;
		*(buff++) = ((w >> 12) & 0x3F) | 0x80;
		*(buff++) = ((w >> 6) & 0x3F) | 0x80;
		*buff = ((w >> 0) & 0x3F) | 0x80;
		return (4);
	}
	return (0);
}

size_t		ft_wstrconv(char *buff, const wchar_t *wstr)
{
	size_t	ans;

	ans = 0;
	while (*wstr != 0)
		ans += ft_widetoa(buff + ans, (wint_t)*(wstr++));
	return (ans);
}

size_t		ft_wstrnconv(char *buff, const wchar_t *wstr, size_t n)
{
	size_t	ans;
	size_t	tmp;

	ans = 0;
	tmp = 0;
	while (*wstr != 0)
	{
		tmp = ft_widetoa(buff + ans, (wint_t)*(wstr++));
		if (ans + tmp > n)
			break ;
		ans += tmp;
	}
	return (ans);
}
