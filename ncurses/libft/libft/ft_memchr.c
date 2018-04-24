/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:14:23 by jyeo              #+#    #+#             */
/*   Updated: 2017/11/10 18:46:05 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*cstr;

	i = 0;
	cstr = (unsigned char*)str;
	while (i < n)
	{
		if (cstr[i] == (unsigned char)c)
			return (cstr + i);
		i++;
	}
	return (0);
}
