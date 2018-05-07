/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:42:52 by rnugroho          #+#    #+#             */
/*   Updated: 2017/11/14 16:42:52 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char		*ptr1;
	const char	*ptr2;
	size_t		i;

	ptr1 = s1;
	while (*ptr1)
		ptr1++;
	ptr2 = s2;
	i = 0;
	while (*ptr2 && i < n)
	{
		*ptr1 = *ptr2;
		ptr2++;
		ptr1++;
		i++;
	}
	*ptr1 = '\0';
	return (s1);
}
