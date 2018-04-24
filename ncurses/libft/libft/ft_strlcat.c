/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:54:39 by jyeo              #+#    #+#             */
/*   Updated: 2017/11/12 07:32:16 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int i;
	unsigned int dst_size;
	unsigned int src_size;

	i = 0;
	dst_size = 0;
	src_size = 0;
	while (dst[dst_size] != '\0')
		dst_size++;
	while (src[src_size] != '\0')
		src_size++;
	if (dst_size < size)
		src_size += dst_size;
	else
		src_size += size;
	if (size == 0)
		return (src_size);
	while (src[i] != '\0' && dst_size + i < size - 1)
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (src_size);
}
