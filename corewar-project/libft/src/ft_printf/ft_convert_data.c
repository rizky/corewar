/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 02:11:04 by rnugroho          #+#    #+#             */
/*   Updated: 2018/02/27 16:43:24 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int
	pf_maxdigit(intmax_t *tab, int len, int quote)
{
	intmax_t	i;
	int			max;

	i = 0;
	max = 0;
	while (i < len)
	{
		if (max < tab[i])
			max = tab[i];
		i++;
	}
	max = ft_strlen(ft_itoa(max));
	if (quote)
		max = max + max / 3;
	return (max);
}

int
	pf_cv_y(t_modifier *m, t_array *d, va_list ap)
{
	intmax_t	*arg;
	int			i;
	int			max;

	arg = va_arg(ap, intmax_t *);
	if (m->size == 0)
		m->size = 1;
	max = pf_maxdigit(arg, m->size * m->precision, m->quote);
	i = -1;
	fta_append(d, "[", 1);
	while (++i < m->size * m->precision)
	{
		if (i % m->precision == 0 && i > 0)
			fta_append(d, "]\n ", 3);
		if (i % m->precision != 0)
			fta_append(d, ", ", 2);
		else
			fta_append(d, "[", 1);
		if (m->quote)
			fta_append(d, ft_rasprintf(&max, "%'*d", max, arg[i]), max);
		else
			fta_append(d, ft_rasprintf(&max, "%*d", max, arg[i]), max);
	}
	fta_append(d, "]]", 2);
	return (1);
}

int
	pf_cv_r(t_modifier *m, t_array *d, va_list ap)
{
	t_list *arg;
	t_list *list;

	(void)m;
	arg = va_arg(ap, t_list*);
	list = arg;
	while (list)
	{
		if (list != arg)
			fta_append(d, " ⟾  ", 6);
		fta_append(d, "[", 1);
		fta_append(d, list->content, ft_strlen(list->content));
		fta_append(d, "]", 1);
		list = list->next;
	}
	return (1);
}

int
	pf_cv_q(t_modifier *m, t_array *d, va_list ap)
{
	double		arg;
	int			q;
	int			ans;
	const char	size[5] = "KMGTP";

	(void)m;
	arg = va_arg(ap, double);
	q = 0;
	while (arg > 1000 && q < 5)
	{
		arg = arg / 1000;
		q++;
	}
	fta_append(d, ft_rasprintf(&ans, "%.1f", arg), ans);
	if (q > 0)
	{
		fta_append(d, &(size[q - 1]), 1);
		ans++;
	}
	return (ans);
}

int
	pf_cv_cq(t_modifier *m, t_array *d, va_list ap)
{
	unsigned char	arg;
	int				i;

	(void)m;
	i = 0;
	if (m->length == 'l')
		return (pf_cv_wc(m, d, ap));
	else
		arg = (char)va_arg(ap, int);
	m->precision = -1;
	while (i < m->size)
	{
		fta_append(d, (void *)&arg, 1);
		i++;
	}
	return (1);
}
