/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 00:57:41 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/12 00:57:43 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		ft_flag_check(const char **s, char **f)
{
	if ((ft_strcmp(*f, " ") == 0 || ft_strcmp(*f, "+") == 0))
	{
		if ((**s) != 'd' && (**s) != 'i' && (**s) != 'D'
			&& ft_strncmp(*s, "ld", 2) != 0 && ft_strncmp(*s, "li", 2) != 0
			&& ft_strncmp(*s, "lld", 3) != 0 && ft_strncmp(*s, "lli", 3) != 0)
			*f = NULL;
	}
	return (0);
}

static	int		ft_flag_init(int *res, t_width *width, t_flag *flag)
{
	*res = 0;
	(*width).width = 0;
	(*width).align = 0;
	(*width).precision = -1;
	(*flag).pad = " ";
	(*flag).f = NULL;
	return (0);
}

static	int		ft_get(const char **str, char **s, va_list ap, int precision)
{
	int res;

	res = 0;
	if ((**str) == 'S' || (**str) == 'C')
		res = ft_type_wchar(s, ap, (**str), precision);
	else
		res = ft_type(str, s, ap);
	return (res);
}

static	int		ft_flag(const char **str, char **buf, va_list ap, char **s)
{
	int		res;
	t_flag	flag;
	t_width	width;

	ft_flag_init(&res, &width, &flag);
	ft_flag_p(str, &flag, &width, ap);
	if (width.width == 0)
		ft_width(str, &width, &flag, 0);
	res = ft_get(str, s, ap, width.precision);
	ft_flag_hash(str, &flag.f, s, &width);
	ft_precision(str, s, &flag, &width);
	width.width -= ft_strlen(*s);
	if ((**str) == 'p')
	{
		flag.f = "0x";
		width.width = width.width - 1;
	}
	if (flag.f)
		ft_flag_check(str, &flag.f);
	width.width += ft_flag0(buf, s, flag);
	if ((**str) == 'c' && (**s) == 0)
		width.width--;
	res += ft_align(buf, s, flag.pad, width);
	return (res);
}

int				ft_format(const char **str, char **buf, va_list ap)
{
	int		i;
	int		res;
	char	*s;
	char	*tmp;

	i = 0;
	res = 0;
	res = ft_flag(str, buf, ap, &s);
	if (res == -1)
		return (0);
	if (((**str) == 'c' || (**str) == 'C') && (*s) == 0)
	{
		res = ft_strlen(*buf) + 1;
		ft_putstr(*buf);
		FREE(*buf);
		*buf = ft_strnew(0);
		ft_putchar((*s));
	}
	JOIN(tmp, *buf, *buf, s);
	FREE(s);
	*str += 1;
	return (res);
}
