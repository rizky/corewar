/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:37:19 by rnugroho          #+#    #+#             */
/*   Updated: 2017/11/14 16:37:19 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_p;
	const char	*src_p;

	dst_p = (char*)dst;
	src_p = (char*)src;
	if (src_p < dst_p)
	{
		while (len--)
			dst_p[len] = src_p[len];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
