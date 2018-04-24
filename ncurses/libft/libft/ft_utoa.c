/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 06:43:21 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/12 06:43:23 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		fill(char *str, unsigned int n, int size)
{
	str[size] = '\0';
	while (size-- > 0)
	{
		str[size] = ((n % 10) + '0');
		n = n / 10;
	}
}

char			*ft_utoa(unsigned int n)
{
	int		size;
	char	*str;

	size = ft_intlen_base(n, 10);
	if ((str = ft_strnew(size)) == NULL)
		return (NULL);
	fill(str, n, size);
	return (str);
}
