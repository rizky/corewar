/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 11:37:05 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/06 16:22:17 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		ft_fill(const char **str, va_list ap, char **buf, int i)
{
	int		res;
	char	*tmp;
	char	*arr;

	arr = ft_strsub(*str, 0, i);
	JOIN(tmp, *buf, *buf, arr);
	FREE(arr);
	i++;
	*str += i;
	res = ft_format(str, buf, ap);
	if (res == -1)
		return (-1);
	return (res);
}

static	int		ft_process(const char *str, va_list ap, char **buf)
{
	int		i;
	int		res;
	char	*tmp;

	i = 0;
	res = 0;
	while (str[i])
	{
		while (str[i] == '%')
		{
			if ((str[i + 1] == 'S' || str[i + 1] == 'C' || (str[i + 1] == 'l'
				&& (str[i + 2] == 's' || str[i + 2] == 'c')))
				&& MB_CUR_MAX != 4)
			{
				return (-1);
			}
			res += ft_fill(&str, ap, buf, i);
			if (res == -1)
				return (-1);
			i = 0;
		}
		i++;
	}
	JOIN(tmp, *buf, *buf, str);
	return (res);
}

int				ft_printf(const char *str, ...)
{
	int		res;
	char	*buf;
	char	*s;
	va_list	ap;

	res = 0;
	buf = ft_strnew(0);
	s = ft_strdup(str);
	va_start(ap, str);
	res = ft_process(s, ap, &buf);
	if (res == -1)
	{
		ft_putstr(buf);
		FREE(buf);
		FREE(s);
		return (-1);
	}
	res += ft_strlen(buf);
	ft_putstr(buf);
	FREE(buf);
	FREE(s);
	va_end(ap);
	return (res);
}
