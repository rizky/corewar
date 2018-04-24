/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:28:44 by jyeo              #+#    #+#             */
/*   Updated: 2017/11/12 03:02:27 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*cdst;
	unsigned char	*csrc;
	unsigned char	*temp;

	i = 0;
	cdst = (unsigned char*)dst;
	csrc = (unsigned char*)src;
	if ((temp = (unsigned char *)malloc(sizeof(*temp) * (n + 1))) == NULL)
		return (dst);
	while (i < n)
	{
		temp[i] = csrc[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		cdst[i] = temp[i];
		i++;
	}
	free(temp);
	temp = NULL;
	return (dst);
}
