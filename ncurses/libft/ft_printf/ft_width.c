/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 20:26:29 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/17 20:26:30 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_width(const char **str, t_width *width, t_flag *flag, int i)
{
	int		j;
	char	*arr;

	j = i;
	(*width).width = 0;
	while ((*str)[i] && ft_isdigit((*str)[i]))
		i++;
	arr = ft_strsub((*str), j, i);
	if (arr != NULL)
		(*width).width = ft_atoi(arr);
	*str += i;
	if ((**str) == '.')
		(*width).precision = ft_get_pres(str);
	if ((*width).precision == 0 && ((**str) != 'o' && (**str) != 'O'
		&& (**str) != 'i' && (**str) != 'd' && (**str) != 'D'))
		(*flag).f = NULL;
	if ((*width).precision == 0)
		(*flag).pad = " ";
	FREE(arr);
	return (0);
}

int			ft_get_pres(const char **str)
{
	int		i;
	int		precision;
	char	*arr;

	i = 0;
	precision = 0;
	(*str)++;
	while ((*str)[i] && ft_isdigit((*str)[i]))
		i++;
	arr = ft_strsub((*str), 0, i);
	precision = ft_atoi(arr);
	FREE(arr);
	*str += i;
	return (precision);
}

static	int	ft_precision_1(const char **str, char **s, t_width *w)
{
	char	*tmp;
	char	*sign;

	if ((*w).precision == 0 && (*s)[0] == '0')
		STRDUP(tmp, *s, "");
	(*w).precision -= ft_strlen(*s);
	if (((**str) == 'd' || (**str) == 'i') && (*s)[0] == '-')
	{
		sign = "-";
		STRDUP(tmp, *s, *s + 1);
		(*w).precision++;
		while ((*w).precision-- > 0)
			JOIN(tmp, *s, "0", *s);
		JOIN(tmp, *s, sign, *s);
	}
	while ((*w).precision-- > 0)
		JOIN(tmp, *s, "0", *s);
	return (0);
}

int			ft_precision(const char **str, char **s, t_flag *flag, t_width *w)
{
	char	*tmp;

	if ((*w).precision >= 0)
	{
		if ((**str) != 'c' && (**str) != 's' && (**str) != '%'
			&& (**str) != 'S')
			(*flag).pad = " ";
		if ((**str) == 's' || (**str) == 'S')
		{
			tmp = *s;
			*s = ft_strndup(*s, (*w).precision);
			FREE(tmp);
			tmp = NULL;
		}
		else if ((**str) == 'd' || (**str) == 'D' || (**str) == 'i'
			|| (**str) == 'u' || (**str) == 'U' || (**str) == 'o'
			|| (**str) == 'p' || (**str) == 'O' || (**str) == 'x'
			|| (**str) == 'X')
		{
			ft_precision_1(str, s, w);
		}
	}
	return (0);
}
