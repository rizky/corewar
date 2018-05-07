/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:36:44 by rnugroho          #+#    #+#             */
/*   Updated: 2017/11/14 16:36:44 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst_p;

	i = 0;
	dst_p = (unsigned char *)s;
	while (i < n)
	{
		if (dst_p[i] == (unsigned char)c)
			return (dst_p + i);
		i++;
	}
	return (NULL);
}
