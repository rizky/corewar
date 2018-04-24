/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:27:32 by jyeo              #+#    #+#             */
/*   Updated: 2017/11/12 07:33:06 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t j;
	size_t size;

	i = 0;
	j = 0;
	size = ft_strlen(to_find);
	if (to_find[j] == '\0')
		return ((char *)str);
	while ((str[i] != '\0') && (size <= len))
	{
		while (str[i + j] == to_find[j] && (str[i] != '\0'))
		{
			if (to_find[j + 1] == '\0')
			{
				return ((char *)str + i);
			}
			j++;
		}
		j = 0;
		len--;
		i++;
	}
	return (0);
}
