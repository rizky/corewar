/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:06:42 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/16 19:06:44 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_flag0(char **buf, char **s, t_flag flag)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_strcmp(flag.pad, "0") == 0)
	{
		if (flag.f && (*s)[0] != '-')
			JOIN(tmp, *buf, *buf, flag.f);
		else if ((*s)[0] == '-')
		{
			JOIN(tmp, *buf, *buf, "-");
			STRDUP(tmp, *s, *s + 1);
			i = 1;
		}
		else
			i = 1;
	}
	else if (ft_strcmp(flag.pad, " ") == 0)
	{
		if (flag.f && (*s)[0] != '-')
			JOIN(tmp, *s, flag.f, *s);
		else
			i = 1;
	}
	return (--i);
}

static	int		ft_flag_p_1(const char **str, t_flag *flag, t_width *w, int i)
{
	if ((*str)[i] == '0')
	{
		if ((*w).align == 0)
			(*flag).pad = "0";
	}
	else if ((*str)[i] == '-')
	{
		(*w).align = 1;
		(*flag).pad = " ";
	}
	else if ((*str)[i] == '+')
		(*flag).f = "+";
	else if ((*str)[i] == ' ' && !(*flag).f)
		(*flag).f = " ";
	else if ((*str)[i] == '#')
		(*flag).f = "#";
	return (0);
}

static	int		ft_flag_p_2(const char **str, t_flag *f, t_width *w, va_list ap)
{
	if (ft_isdigit((*str)[0]) || (*str)[0] == '.')
	{
		if ((*w).width == 0)
		{
			ft_width(str, w, f, 0);
			*str -= 1;
		}
		if ((*str)[1] == '*')
		{
			(*w).precision = va_arg(ap, int);
			*str += 1;
		}
	}
	else if ((*str)[0] == '*')
	{
		(*w).width = va_arg(ap, int);
		if ((*w).width < 0)
		{
			(*w).align = 1;
			(*f).pad = " ";
			(*w).width *= -1;
		}
	}
	return (0);
}

int				ft_flag_p(const char **st, t_flag *flag, t_width *w, va_list ap)
{
	int i;

	i = 0;
	while ((*st)[i] && ((*st)[i] == '0' || (*st)[i] == ' ' || (*st)[i] == '*'
		|| (*st)[i] == '+' || (*st)[i] == '-' || (*st)[i] == '#'
		|| (*st)[i] == '.' || ft_isdigit((*st)[i])))
	{
		if ((*st)[i] == '0' || (*st)[i] == '-' || (*st)[i] == '+'
			|| (*st)[i] == ' ' || (*st)[i] == '#')
		{
			ft_flag_p_1(st, flag, w, i);
		}
		else if (ft_isdigit((*st)[i]) || (*st)[i] == '.' || (*st)[i] == '*')
		{
			*st += i;
			ft_flag_p_2(st, flag, w, ap);
			i = 0;
		}
		i++;
	}
	*st += i;
	return (0);
}

int				ft_align(char **buf, char **s, char *padding, t_width width)
{
	char	*tmp;

	if (width.align)
	{
		while (width.width-- > 0)
			JOIN(tmp, *s, *s, padding);
	}
	else
	{
		while (width.width-- > 0)
			JOIN(tmp, *buf, *buf, padding);
	}
	return (0);
}
