/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:42:01 by rnugroho          #+#    #+#             */
/*   Updated: 2017/11/14 16:42:01 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*d;
	const char	*s;
	size_t		slen;
	size_t		dlen;

	d = dst;
	s = src;
	dlen = ft_strlen(dst);
	if (dstsize < dlen)
		dlen = dstsize;
	slen = dstsize - dlen;
	if (slen == 0)
		return (dlen + ft_strlen(s));
	d = dst + dlen;
	while (*s != '\0')
	{
		if (slen != 1)
		{
			*d++ = *s;
			slen--;
		}
		s++;
	}
	*d = '\0';
	return (dlen + (s - src));
}
