/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:36:14 by rnugroho          #+#    #+#             */
/*   Updated: 2018/02/18 18:39:04 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_vprintf(char const *format, va_list ap)
{
	return (ft_vdprintf(1, format, ap));
}

int		ft_vdprintf(int fd, char const *format, va_list ap)
{
	char		*str;
	int			ans;

	ans = ft_vasprintf(&str, format, ap);
	if (ans == -1)
		write(fd, str, ft_strlen(str));
	else
		write(fd, str, ans);
	free(str);
	return (ans);
}
