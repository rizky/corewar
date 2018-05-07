/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:36:36 by rnugroho          #+#    #+#             */
/*   Updated: 2017/11/14 16:36:36 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst,
			const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*src_p;
	unsigned char	*dst_p;

	i = 0;
	src_p = (unsigned char *)src;
	dst_p = (unsigned char *)dst;
	while (i < n)
	{
		dst_p[i] = src_p[i];
		if (src_p[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
