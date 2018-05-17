/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_numeric_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:54:20 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/21 16:08:09 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int
	pf_culturization(t_array *d, char c)
{
	t_array temp;
	int		i;

	i = 1;
	temp = NEW_ARRAY(char);
	while (ft_isdigit((ARRAY_LAST(d))[0]))
	{
		fta_append(&temp, ARRAY_LAST(d), 1);
		fta_popback(d, 1);
		if (i % 3 == 0)
			fta_append(&temp, &c, 1);
		i++;
	}
	while (temp.size > 0)
	{
		fta_append(d, ARRAY_LAST(&temp), 1);
		fta_popback(&temp, 1);
	}
	return (i / 3);
}

/*
** pf_itoa_base appends _n_ expressed in base _b_ in _d_
** if the weakest bit of _info_ is on, capital letters will be used
** |  for digits greater than 10.
** if the second weakest bit of _info_ is on, _n_ is considered unsigned.
*/

int
	pf_itoa_base(t_array *d, intmax_t n, int b, char info)
{
	int					ans;
	const uintmax_t		un = (uintmax_t)n;
	const char *const	base =

	(info & 1 ? "0123456789ABCDEF" : "0123456789abcdef");
	ans = 1;
	if (info & 2 ? (uintmax_t)b <= un : n <= -b || b <= n)
		ans += pf_itoa_base(d, (info & 2 ?
			(intmax_t)(un / b) : n / b), b, info);
	fta_append(d, (void *)(base +
		(info & 2 ? (size_t)(un % b) : ABS(n % b))), 1);
	return (ans);
}

/*
** Converts a unsigned integer into octal representation oooo.
*/

int
	pf_cv_o(t_modifier *m, t_array *d, va_list ap)
{
	int alt;

	alt = 0;
	if (m->booleans.n.alternate)
	{
		fta_append(d, "0", 1);
		alt = 1;
	}
	m->conversion = 'o';
	return (pf_unsigned_integer(m, d, ap, 8) + alt);
}

/*
** Converts a unsigned integer into binary representation bbbb.
*/

int
	pf_cv_b(t_modifier *m, t_array *d, va_list ap)
{
	if (m->booleans.n.alternate)
		fta_append(d, "b", 1);
	return (pf_unsigned_integer(m, d, ap, 2));
}

/*
** returns the number of characters written so far by this call to the function.
*/

int
	pf_cv_n(t_modifier *m, t_array *d, va_list ap)
{
	int		*arg;

	arg = va_arg(ap, void *);
	if (!arg)
		return (0);
	m->size = 0;
	m->precision = -1;
	if (m->length == 'H')
		*(char *)arg = (char)d->size;
	else if (m->length == 'h')
		*(short *)arg = (short)d->size;
	else if (m->length == 'l' || m->length == 'z')
		*(long *)arg = (long)d->size;
	else if (m->length == '7')
		*(long long *)arg = (long long)d->size;
	else if (m->length == 'j')
		*(intmax_t *)arg = (intmax_t)d->size;
	else
		*(int *)arg = (int)d->size;
	return (0);
}
