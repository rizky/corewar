/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_length_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 06:53:30 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/22 06:53:31 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_length_ll_2(const char **str, char **s, va_list ap)
{
	char *tmp;

	if ((*str)[0] == '#' && ((*str)[1] == 'x' || (*str)[1] == 'X'))
	{
		*s = ft_lltoa_base(va_arg(ap, long long int), 16);
		JOIN(tmp, *s, "0x", *s);
		if ((*str)[1] == 'X')
			ft_capitalize(s);
		*str += 1;
	}
	else if ((*str)[0] == 'h' || (*str)[0] == 'j' || (*str)[0] == 'z')
		ERROR((ft_length_ll(str, s, ap)) == -1, -1);
	else
		return (-1);
	return (0);
}

int			ft_length_ll(const char **str, char **s, va_list ap)
{
	(*str)++;
	if ((*str)[0] == 'd' || (*str)[0] == 'i' || (*str)[0] == 'D')
		*s = ft_lltoa(va_arg(ap, long long int));
	else if ((*str)[0] == 'x' || (*str)[0] == 'X')
	{
		*s = ft_lltoa_base(va_arg(ap, long long int), 16);
		if ((*str)[0] == 'X')
			ft_capitalize(s);
	}
	else if ((*str)[0] == 'u' || (*str)[0] == 'U')
		*s = ft_ulltoa(va_arg(ap, unsigned long long int));
	else if ((*str)[0] == 'o' || (*str)[0] == 'O')
		*s = ft_lltoa_base(va_arg(ap, long long int), 8);
	else
		ERROR((ft_length_ll_2(str, s, ap)) == -1, -1);
	return (0);
}

static	int	ft_length_hh_2(const char **str, char **s, va_list ap)
{
	if ((*str)[0] == 'l')
		ERROR((ft_length_l(str, s, ap)) == -1, -1);
	else if ((*str)[0] == 'j' || (*str)[0] == 'z')
		ERROR((ft_length_hh(str, s, ap)) == -1, -1);
	else
		return (-1);
	return (0);
}

int			ft_length_hh(const char **str, char **s, va_list ap)
{
	(*str)++;
	if ((*str)[0] == 'd' || (*str)[0] == 'i')
		*s = ft_itoa((char)va_arg(ap, int));
	else if ((*str)[0] == 'x' || (*str)[0] == 'X')
	{
		*s = ft_itoa_base((unsigned char)va_arg(ap, int), 16);
		if ((*str)[0] == 'X')
			ft_capitalize(s);
	}
	else if ((*str)[0] == 'u')
		*s = ft_utoa((unsigned char)va_arg(ap, int));
	else if ((*str)[0] == 'U' || (*str)[0] == 'D')
		*s = ft_utoa((unsigned short)va_arg(ap, int));
	else if ((*str)[0] == 'o')
		*s = ft_itoa_base((unsigned char)va_arg(ap, int), 8);
	else if ((*str)[0] == 'O')
		*s = ft_itoa_base((unsigned short)va_arg(ap, int), 8);
	else if ((*str)[0] == 'S' || (*str)[0] == 'C')
		ft_type_wchar(s, ap, (*str)[0], -1);
	else
		ERROR((ft_length_hh_2(str, s, ap)) == -1, -1);
	return (0);
}
