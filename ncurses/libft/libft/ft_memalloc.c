/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 21:28:48 by jyeo              #+#    #+#             */
/*   Updated: 2017/11/13 07:15:54 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned int	i;
	void			*new;

	i = 0;
	if ((new = (unsigned char *)malloc(sizeof(*new) * (size))) == NULL)
		return (NULL);
	ft_bzero(new, size);
	return (new);
}
