/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_date.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 00:50:57 by rnugroho          #+#    #+#             */
/*   Updated: 2018/02/27 13:24:32 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void
	pf_date_format_date(t_array *d, long *res_date)
{
	const char	*months[12] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November",
		"December"};

	fta_append(d, ft_itoa(res_date[3]), ft_strlen(ft_itoa(res_date[3])));
	fta_append(d, " ", 1);
	fta_append(d, months[res_date[4]], ft_strlen(months[res_date[4]]));
	fta_append(d, " ", 1);
	fta_append(d, ft_itoa(res_date[5]), ft_strlen(ft_itoa(res_date[5])));
}

static void
	pf_date_format_time(t_array *d, long *res_date)
{
	if (res_date[2] < 10)
		fta_append(d, "0", 1);
	fta_append(d, ft_itoa(res_date[2]), ft_strlen(ft_itoa(res_date[2])));
	fta_append(d, ":", 1);
	if (res_date[1] < 10)
		fta_append(d, "0", 1);
	fta_append(d, ft_itoa(res_date[1]), ft_strlen(ft_itoa(res_date[1])));
	fta_append(d, ":", 1);
	if (res_date[0] < 10)
		fta_append(d, "0", 1);
	fta_append(d, ft_itoa(res_date[0]), ft_strlen(ft_itoa(res_date[0])));
}

int
	pf_cv_ct(t_modifier *m, t_array *d, va_list ap)
{
	long long	arg;

	arg = va_arg(ap, long long);
	if (m->size == 1)
		pf_date_format_date(d, ft_epochtodate(arg));
	else if (m->size == 2)
		pf_date_format_time(d, ft_epochtodate(arg));
	else
	{
		pf_date_format_date(d, ft_epochtodate(arg));
		fta_append(d, ", ", 2);
		pf_date_format_time(d, ft_epochtodate(arg));
	}
	return (1);
}
