/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:27:18 by jyeo              #+#    #+#             */
/*   Updated: 2017/11/12 07:30:08 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (str[size] != '\0')
		size++;
	while (i < size + 1)
	{
		if (str[i] == c)
			return ((char *)str + i);
		i++;
	}
	return (0);
}
