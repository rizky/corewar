/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_double_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:37:10 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/01 00:24:04 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int
	pf_finde(long double *arg, int *ans, t_array *d, int e)
{
	if (*arg < 100000 && *arg >= 0.0001)
		return (e);
	if (*arg > 0 && *arg < 1)
	{
		if (((int)((*arg) * 10) % 10) != 0)
		{
			*ans = fta_append(d, "0.", 2);
			*arg = *arg * 10;
		}
		else
		{
			while (*arg > 0 && *arg < 1)
			{
				*arg = *arg * 10;
				e--;
			}
		}
	}
	while (*arg > 9)
	{
		*arg = *arg / 10;
		e++;
	}
	return (e);
}

static int
	pf_findp(long double *arg, int p)
{
	while (*arg > 0 && *arg < 1)
	{
		*arg = *arg * 2;
		p--;
	}
	while (*arg >= 2)
	{
		*arg = *arg / 2;
		p++;
	}
	return (p);
}

static int
	pf_findlp(long double *arg, int p)
{
	if (*arg > 0 && *arg < 1)
	{
		while (*arg < 16)
		{
			*arg = *arg * 2;
			p--;
		}
	}
	while (*arg >= 16)
	{
		*arg = *arg / 2;
		p++;
	}
	return (p);
}

int
	pf_signed_double_g(t_modifier *m, t_array *d, long double arg, char *c)
{
	int		ans;
	int		e;

	e = 0;
	e = pf_finde(&arg, &ans, d, e);
	ans = pf_rtoa(d, ABS(arg), 10, m);
	fta_popzero(d, &ans);
	if (e == 0)
	{
		m->precision = -1;
		return (ans);
	}
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

int
	pf_signed_double_a(t_modifier *m, t_array *d, long double arg, char *c)
{
	int		ans;
	int		p;

	p = 0;
	p = (m->length == 'L' ? pf_findlp(&arg, p) : pf_findp(&arg, p));
	if (*c == 'p')
		ans = pf_rtoa(d, ABS(arg), 16, m);
	else
		ans = pf_rtoa(d, ABS(arg), -16, m);
	if (m->precision == -1)
		fta_popzerohex(d, &ans);
	ans += fta_append(d, c, 1);
	if (p >= 0)
		ans += fta_append(d, "+", 1);
	else
		ans += fta_append(d, "-", 1);
	pf_itoa_base(d, p, 10, 0);
	return (ans);
}
