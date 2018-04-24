/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_length.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 05:33:05 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/18 05:33:07 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_length_j(const char **str, char **s, va_list ap)
{
	(*str)++;
	if ((*str)[0] == 'd' || (*str)[0] == 'i' || (*str)[0] == 'D')
		*s = ft_ltoa(va_arg(ap, intmax_t));
	else if ((*str)[0] == 'x' || (*str)[0] == 'X')
	{
		*s = ft_ltoa_base(va_arg(ap, uintmax_t), 16);
		if ((*str)[0] == 'X')
			ft_capitalize(s);
	}
	else if ((*str)[0] == 'u' || (*str)[0] == 'U')
		*s = ft_ultoa(va_arg(ap, uintmax_t));
	else if ((*str)[0] == 'o' || (*str)[0] == 'O')
		*s = ft_ltoa_base(va_arg(ap, uintmax_t), 8);
	else if ((*str)[0] == 'l' || (*str)[0] == 'h' || (*str)[0] == 'j'
		|| (*str)[0] == 'z')
		ERROR((ft_length_j(str, s, ap)) == -1, -1);
	else
		return (-1);
	return (0);
}

static	int	ft_length_z(const char **str, char **s, va_list ap)
{
	(*str)++;
	if ((*str)[0] == 'd' || (*str)[0] == 'i' || (*str)[0] == 'D')
		*s = ft_ltoa(va_arg(ap, size_t));
	else if ((*str)[0] == 'u' || (*str)[0] == 'U')
		*s = ft_ultoa(va_arg(ap, size_t));
	else if ((*str)[0] == 'o' || (*str)[0] == 'O')
		*s = ft_ltoa_base(va_arg(ap, size_t), 8);
	else if ((*str)[0] == 'x' || (*str)[0] == 'X')
	{
		*s = ft_ltoa_base(va_arg(ap, size_t), 16);
		if ((*str)[0] == 'X')
			ft_capitalize(s);
	}
	else if ((*str)[0] == 'l' || (*str)[0] == 'h' || (*str)[0] == 'j'
		|| (*str)[0] == 'z')
		ERROR((ft_length_z(str, s, ap)) == -1, -1);
	else
		return (-1);
	return (0);
}

int			ft_length_l(const char **str, char **s, va_list ap)
{
	(*str)++;
	if ((*str)[0] == 'l')
		ERROR((ft_length_ll(str, s, ap)) == -1, -1);
	else if ((*str)[0] == 'd' || (*str)[0] == 'i' || (*str)[0] == 'D')
		*s = ft_ltoa(va_arg(ap, long int));
	else if ((*str)[0] == 'x' || (*str)[0] == 'X')
	{
		*s = ft_ltoa_base(va_arg(ap, long int), 16);
		if ((*str)[0] == 'X')
			ft_capitalize(s);
	}
	else if ((*str)[0] == 'u' || (*str)[0] == 'U')
		*s = ft_ultoa(va_arg(ap, unsigned long int));
	else if ((*str)[0] == 'o' || (*str)[0] == 'O')
		*s = ft_ltoa_base(va_arg(ap, long int), 8);
	else if ((*str)[0] == 's' || (*str)[0] == 'c')
		ft_type_wchar(s, ap, ft_toupper((*str)[0]), -1);
	else if ((*str)[0] == 'p')
		ft_type(str, s, ap);
	else if ((*str)[0] == 'h' || (*str)[0] == 'j' || (*str)[0] == 'z')
		ERROR((ft_length_l(str, s, ap)) == -1, -1);
	else
		return (-1);
	return (0);
}

static	int	ft_length_h(const char **str, char **s, va_list ap)
{
	(*str)++;
	if ((*str)[0] == 'h')
		ERROR((ft_length_hh(str, s, ap)) == -1, -1);
	else if ((*str)[0] == 'd' || (*str)[0] == 'i')
		*s = ft_itoa((short)va_arg(ap, int));
	else if ((*str)[0] == 'x' || (*str)[0] == 'X')
	{
		*s = ft_itoa_base((unsigned short)va_arg(ap, int), 16);
		if ((*str)[0] == 'X')
			ft_capitalize(s);
	}
	else if ((*str)[0] == 'u' || (*str)[0] == 'D')
		*s = ft_utoa((unsigned short)va_arg(ap, int));
	else if ((*str)[0] == 'U')
		*s = ft_ultoa(va_arg(ap, unsigned long int));
	else if ((*str)[0] == 'o' || (*str)[0] == 'O')
		*s = ft_itoa_base((unsigned short)va_arg(ap, int), 8);
	else if ((*str)[0] == 'l' || (*str)[0] == 'j' || (*str)[0] == 'z')
		ERROR((ft_length_h(str, s, ap)) == -1, -1);
	else
		return (-1);
	return (0);
}

int			ft_length(const char **str, char **s, va_list ap, int i)
{
	if ((*str)[i] == 'h')
		ERROR((ft_length_h(str, s, ap)) == -1, -1);
	else if ((*str)[i] == 'l')
		ERROR((ft_length_l(str, s, ap)) == -1, -1);
	else if ((*str)[i] == 'z')
		ERROR((ft_length_z(str, s, ap)) == -1, -1);
	else if ((*str)[i] == 'j')
		ERROR((ft_length_j(str, s, ap)) == -1, -1);
	else
		return (-1);
	return (0);
}
