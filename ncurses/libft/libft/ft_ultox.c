/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 08:18:31 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/12 08:18:33 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_intlen_base_long(unsigned int long n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 16;
		size++;
	}
	return (size);
}

static void		fill(char *str, unsigned long int n, int size)
{
	str[size] = '\0';
	while (size-- > 0)
	{
		if (n % 16 > 9)
			str[size] = (((n % 16) - 10) + 'a');
		else
			str[size] = ((n % 16) + '0');
		n = n / 16;
	}
}

char			*ft_ultox(unsigned int long n)
{
	int		size;
	char	*str;

	size = ft_intlen_base_long(n);
	if ((str = ft_strnew(size)) == NULL)
		return (NULL);
	fill(str, n, size);
	return (str);
}
