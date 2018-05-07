/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_double_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 09:34:08 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/01 14:35:58 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int
	pf_rtoa(t_array *d, long double x, int b, t_modifier *m)
{
	double			frac;
	int				ans;
	int				bp;
	int				p;

	ans = 1 + pf_itoa_base(d, (intmax_t)x, ABS(b), (b < 0));
	if (m->quote)
		ans += pf_culturization(d, ',');
	if (m->precision == 0)
		return (ans);
	fta_append(d, ".", 1);
	bp = -1;
	frac = ft_modf(x);
	p = (m->precision == -1 ? 13 : m->precision);
	while (++bp < p)
	{
		frac *= ABS(b);
		if (frac < 1)
			fta_append(d, "0", 1);
		ans++;
	}
	frac = ft_round_base(frac, ft_modf(frac), ABS(b));
	if (frac != 0)
		pf_itoa_base(d, (long long)frac, ABS(b), 2 | (b < 0));
	return (ans);
}

int
	pf_cv_f(t_modifier *m, t_array *d, va_list ap)
{
	long double	arg;

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
	if (arg == 0 && m->precision == 0)
		return (0);
	if (m->precision == -1)
		m->precision = 6;
	if (arg != arg || arg == 1.0 / 0.0)
	{
		if (arg == 1.0 / 0.0)
			fta_append(d, "inf", 3);
		else
			fta_append(d, "nan", 3);
		return (0);
	}
	return (pf_rtoa(d, ABS(arg), 10, m));
}

int
	pf_cv_cf(t_modifier *m, t_array *d, va_list ap)
{
	long double	arg;

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
	if (arg == 0 && m->precision == 0)
		return (0);
	if (m->precision == -1)
		m->precision = 6;
	if (arg != arg || arg == 1.0 / 0.0)
	{
		if (arg == 1.0 / 0.0)
			fta_append(d, "INF", 3);
		else
			fta_append(d, "NAN", 3);
		return (0);
	}
	return (pf_rtoa(d, ABS(arg), 10, m));
}

int
	pf_cv_e(t_modifier *m, t_array *d, va_list ap)
{
	long double	arg;

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
	return (pf_signed_double_e(m, d, arg, "e"));
}

int
	pf_cv_ce(t_modifier *m, t_array *d, va_list ap)
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
	return (pf_signed_double_e(m, d, arg, "E"));
}
