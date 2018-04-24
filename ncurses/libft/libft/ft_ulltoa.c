/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 06:14:20 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/20 06:14:22 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_llong_len(unsigned long long int n)
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

static void		fill(char *str, unsigned long long int n, int size)
{
	str[size] = '\0';
	while (size-- > 0)
	{
		str[size] = ((n % 10) + '0');
		n = n / 10;
	}
}

char			*ft_ulltoa(unsigned long long int n)
{
	int		size;
	char	*str;

	size = ft_llong_len(n);
	if ((str = ft_strnew(size)) == NULL)
		return (NULL);
	fill(str, n, size);
	return (str);
}
