/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 22:27:14 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/15 20:56:13 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int
	pf_cv_w(t_modifier *m, t_array *d, va_list ap)
{
	int		index;
	char	*value;

	(void)ap;
	index = m->size;
	m->size = 0;
	if (index > 6)
		index = 0;
	if (index != 0)
		index += 30;
	fta_append(d, "\e[", 2);
	fta_append(d, "0;", 2);
	value = ft_itoa(index);
	fta_append(d, value, ft_strlen(value));
	fta_append(d, "m", 1);
	free(value);
	return (1);
}

int
	pf_cv_cw(t_modifier *m, t_array *d, va_list ap)
{
	int		index;
	char	*value;

	(void)ap;
	index = m->size;
	m->size = 0;
	if (index > 6)
		index = 0;
	if (index != 0)
		index += 30;
	fta_append(d, "\e[", 2);
	fta_append(d, "1;", 2);
	value = ft_itoa(index);
	fta_append(d, value, ft_strlen(value));
	fta_append(d, "m", 1);
	free(value);
	return (1);
}

int
	pf_cv_v(t_modifier *m, t_array *d, va_list ap)
{
	int		row;
	int		col;
	char	*value;

	(void)ap;
	row = m->size;
	col = m->precision;
	m->size = 0;
	m->precision = -1;
	fta_append(d, "\033[", 2);
	value = ft_itoa(row);
	fta_append(d, value, ft_strlen(value));
	fta_append(d, ";", 1);
	free(value);
	value = ft_itoa(col);
	fta_append(d, value, ft_strlen(value));
	fta_append(d, "H", 1);
	free(value);
	return (1);
}
