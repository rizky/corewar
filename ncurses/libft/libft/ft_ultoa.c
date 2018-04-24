/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 05:55:57 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/20 05:55:58 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_long_len(unsigned long int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static void		fill(char *str, unsigned long int n, int size)
{
	str[size] = '\0';
	while (size-- > 0)
	{
		str[size] = ((n % 10) + '0');
		n = n / 10;
	}
}

char			*ft_ultoa(unsigned long int n)
{
	int		size;
	char	*str;

	size = ft_long_len(n);
	if ((str = ft_strnew(size)) == NULL)
		return (NULL);
	fill(str, n, size);
	return (str);
}
