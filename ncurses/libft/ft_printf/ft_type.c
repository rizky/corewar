/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 23:18:50 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/15 23:18:51 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_wchar_string(char **s, int *tab, int p)
{
	int		x;
	char	*arr;
	char	*tmp;

	x = 0;
	*s = ft_strnew(0);
	while (tab[x])
	{
		arr = ft_unicode(tab[x]);
		if (p >= 0 && ((unsigned)p < (ft_strlen(*s) + ft_strlen(arr))))
		{
			FREE(arr);
			return (0);
		}
		JOIN(tmp, *s, *s, arr);
		FREE(arr);
		x++;
	}
	return (0);
}

int			ft_type_wchar(char **s, va_list ap, char type, int p)
{
	int		word;
	int		*tab;

	if (type == 'S')
	{
		tab = va_arg(ap, wchar_t*);
		if (!tab)
			*s = ft_strdup("(null)");
		else
			ft_wchar_string(s, tab, p);
	}
	else if (type == 'C')
	{
		word = va_arg(ap, wchar_t);
		if (word < 0)
			return (-1);
		*s = ft_unicode(word);
	}
	return (0);
}

static	int	ft_type_num(const char **str, char **s, va_list ap, int i)
{
	if ((*str)[i] == 'd' || (*str)[i] == 'i')
		*s = ft_itoa(va_arg(ap, int));
	else if ((*str)[i] == 'u')
		*s = ft_utoa(va_arg(ap, unsigned int));
	else if ((*str)[i] == 'U')
		*s = ft_ultoa(va_arg(ap, unsigned long int));
	else if ((*str)[i] == 'D')
		*s = ft_ltoa(va_arg(ap, long int));
	else if ((*str)[i] == 'o')
		*s = ft_itoa_base(va_arg(ap, int), 8);
	else if ((*str)[i] == 'O')
		*s = ft_ltoa_base(va_arg(ap, unsigned long int), 8);
	else if ((*str)[i] == 'b')
		*s = ft_ltoa_base(va_arg(ap, unsigned long int), 2);
	else if ((*str)[i] == 'x' || (*str)[i] == 'X')
	{
		*s = ft_itoa_base(va_arg(ap, int), 16);
		if ((*str)[i] == 'X')
			ft_capitalize(s);
	}
	else if ((*str)[i] == 'p')
		*s = ft_ltoa_base(va_arg(ap, uintmax_t), 16);
	else
		ERROR((ft_length(str, s, ap, i)) == -1, -1);
	return (0);
}

static	int	ft_type_char(const char **str, char **s, va_list ap, int i)
{
	char	*arr;

	if ((*str)[i] == 's')
	{
		arr = va_arg(ap, char*);
		if (!arr)
			*s = ft_strdup("(null)");
		else
			*s = ft_strdup(arr);
	}
	else if ((*str)[i] == 'c')
	{
		*s = ft_strnew(1);
		(*s)[0] = va_arg(ap, int);
		(*s)[1] = '\0';
	}
	return (0);
}

int			ft_type(const char **str, char **s, va_list ap)
{
	int		i;
	int		res;
	char	*tmp;

	i = 0;
	res = 0;
	*s = ft_strnew(0);
	tmp = *s;
	if ((*str)[i] == 's' || (*str)[i] == 'c')
		ft_type_char(str, s, ap, i);
	else if ((*str)[i] == '%')
		*s = ft_strdup("%");
	else
	{
		if ((ft_type_num(str, s, ap, i) == -1))
		{
			FREE(tmp);
			return (-1);
		}
	}
	FREE(tmp);
	return (res);
}
