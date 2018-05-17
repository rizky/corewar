/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_double_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:36:25 by rnugroho          #+#    #+#             */
/*   Updated: 2018/02/28 23:14:35 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int
	pf_cv_g(t_modifier *m, t_array *d, va_list ap)
{
	double	arg;

	if (m->length == 'L')
		arg = va_arg(ap, long double);
	else
		arg = va_arg(ap, double);
	if (arg < 0)
		fta_append(d, "-", 1);
	else if (m->booleans.n.plus)
		fta_append(d, "+", 1);
	else if (m->booleans.n.space)
		fta_append(d, " ", 1);
	if (m->precision == -1)
		m->precision = 6;
	arg = ABS(arg);
	if (m->precision != 0)
		m->precision = m->precision - 1;
	return (pf_signed_double_g(m, d, arg, "e"));
}

int
	pf_cv_cg(t_modifier *m, t_array *d, va_list ap)
{
	double	arg;

	if (m->length == 'L')
		arg = va_arg(ap, long double);
	else
		arg = va_arg(ap, double);
	if (arg < 0)
		fta_append(d, "-", 1);
	else if (m->booleans.n.plus)
		fta_append(d, "+", 1);
	else if (m->booleans.n.space)
		fta_append(d, " ", 1);
	if (m->precision == -1)
		m->precision = 6;
	arg = ABS(arg);
	if (m->precision != 0)
		m->precision = m->precision - 1;
	return (pf_signed_double_g(m, d, arg, "E"));
}

int
	pf_cv_a(t_modifier *m, t_array *d, va_list ap)
{
	double	arg;

	if (m->length == 'L')
		arg = va_arg(ap, long double);
	else
		arg = va_arg(ap, double);
	if (arg < 0)
		fta_append(d, "-", 1);
	else if (m->booleans.n.plus)
		fta_append(d, "+", 1);
	else if (m->booleans.n.space)
		fta_append(d, " ", 1);
	fta_append(d, "0x", 2);
	arg = ABS(arg);
	return (pf_signed_double_a(m, d, arg, "p"));
}

int
	pf_cv_ca(t_modifier *m, t_array *d, va_list ap)
{
	double	arg;

	if (m->length == 'L')
		arg = va_arg(ap, long double);
	else
		arg = va_arg(ap, double);
	if (arg < 0)
		fta_append(d, "-", 1);
	else if (m->booleans.n.plus)
		fta_append(d, "+", 1);
	else if (m->booleans.n.space)
		fta_append(d, " ", 1);
	fta_append(d, "0X", 2);
	arg = ABS(arg);
	return (pf_signed_double_a(m, d, arg, "P"));
}

int
	pf_signed_double_e(t_modifier *m, t_array *d, long double arg, char *c)
{
	int		ans;
	int		e;

	e = 0;
	while (arg > 0 && arg < 1)
	{
		arg = arg * 10;
		e--;
	}
	while (arg > 9)
	{
		arg = arg / 10;
		e++;
	}
	ans = pf_rtoa(d, ABS(arg), 10, m);
	ans += fta_append(d, c, 1);
	if (e >= 0)
		ans += fta_append(d, "+", 1);
	else
		ans += fta_append(d, "-", 1);
	if (ABS(e) < 10)
		ans += fta_append(d, "0", 1);
	pf_itoa_base(d, e, 10, 0);
	return (ans);
}
