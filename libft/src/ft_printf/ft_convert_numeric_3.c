/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_numeric_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 09:34:16 by rnugroho          #+#    #+#             */
/*   Updated: 2018/02/25 01:48:20 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t
	pf_getarg_signed_integer(va_list ap, t_modifier *m)
{
	intmax_t	arg;

	if (m->length == 'H')
		arg = (signed char)va_arg(ap, int);
	else if (m->length == 'h')
		arg = (short)va_arg(ap, int);
	else if (m->length == 'l' || m->length == 'z')
		arg = va_arg(ap, long);
	else if (m->length == '7')
		arg = va_arg(ap, long long);
	else if (m->length == 'j')
		arg = va_arg(ap, intmax_t);
	else if (m->length == 't')
		arg = va_arg(ap, ptrdiff_t);
	else
		arg = va_arg(ap, int);
	return (arg);
}

static uintmax_t
	pf_getarg_unsigned_integer(va_list ap, t_modifier *m)
{
	uintmax_t	arg;

	if (m->length == 'H')
		arg = (unsigned char)va_arg(ap, unsigned);
	else if (m->length == 'h')
		arg = (unsigned short)va_arg(ap, unsigned);
	else if (m->length == 'l')
		arg = va_arg(ap, unsigned long);
	else if (m->length == '7')
		arg = va_arg(ap, unsigned long long);
	else if (m->length == 'z')
		arg = va_arg(ap, size_t);
	else if (m->length == 'j')
		arg = va_arg(ap, uintmax_t);
	else if (m->length == 't')
		arg = va_arg(ap, size_t);
	else
		arg = va_arg(ap, unsigned);
	return (arg);
}

int
	pf_signed_integer(t_modifier *m, t_array *d, va_list ap, int b)
{
	intmax_t	arg;
	int			ans;

	arg = pf_getarg_signed_integer(ap, m);
	if (arg < 0)
		fta_append(d, "-", 1);
	else if (m->booleans.n.plus)
		fta_append(d, "+", 1);
	else if (m->booleans.n.space)
		fta_append(d, " ", 1);
	if (arg == 0 && m->precision == 0)
		return (0);
	ans = pf_itoa_base(d, arg, ABS(b), b < 0);
	if (m->quote)
		ans += pf_culturization(d, ',');
	return (ans);
}

int
	pf_unsigned_integer(t_modifier *m, t_array *d, va_list ap, int b)
{
	uintmax_t	arg;
	int			ans;

	arg = pf_getarg_unsigned_integer(ap, m);
	if (arg == 0 && m->booleans.n.alternate
		&& (m->conversion == 'x' || m->conversion == 'X'))
		d->size -= 2;
	if ((arg == 0 && m->precision == 0) ||
	(arg == 0 && m->conversion == 'o' && m->booleans.n.alternate))
		return (0);
	ans = pf_itoa_base(d, arg, ABS(b), 2 | (b < 0));
	if (m->quote)
		ans += pf_culturization(d, ',');
	return (ans);
}
