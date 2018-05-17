/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_numeric_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:54:46 by rnugroho          #+#    #+#             */
/*   Updated: 2018/02/23 15:41:34 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Converts a signed integer into decimal representation [-]dddd.
*/

int
	pf_cv_di(t_modifier *m, t_array *d, va_list ap)
{
	return (pf_signed_integer(m, d, ap, 10));
}

/*
** Converts an unsigned integer into decimal representation dddd.
*/

int
	pf_cv_u(t_modifier *m, t_array *d, va_list ap)
{
	return (pf_unsigned_integer(m, d, ap, 10));
}

/*
** Converts an unsigned integer into hexadecimal representation hhhh.
*/

int
	pf_cv_x(t_modifier *m, t_array *d, va_list ap)
{
	if (m->booleans.n.alternate)
		fta_append(d, "0x", 2);
	return (pf_unsigned_integer(m, d, ap, 16));
}

/*
** Converts an unsigned integer into hexadecimal representation HHHH.
*/

int
	pf_cv_cx(t_modifier *m, t_array *d, va_list ap)
{
	if (m->booleans.n.alternate)
		fta_append(d, "0X", 2);
	return (pf_unsigned_integer(m, d, ap, -16));
}

/*
** Writes an implementation defined character sequence defining a pointer.
*/

int
	pf_cv_p(t_modifier *m, t_array *d, va_list ap)
{
	(void)m;
	fta_append(d, "0x", 2);
	m->length = '7';
	return (pf_unsigned_integer(m, d, ap, 16));
}
