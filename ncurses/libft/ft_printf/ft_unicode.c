/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 05:14:48 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/13 05:14:49 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*ft_split_mask(char *mask, int size)
{
	int		i;
	int		j;
	char	*binary;
	char	*tmp;

	size /= 8;
	i = 0;
	j = 0;
	binary = ft_strnew(size);
	while (size > 0)
	{
		tmp = ft_strnew(8);
		while (i < 8)
		{
			tmp[i] = mask[i];
			i++;
		}
		mask = mask + i;
		i = 0;
		size--;
		binary[j] = ft_atoi_base(tmp, 2);
		j++;
		FREE(tmp);
	}
	return (binary);
}

static	int		*ft_get_unicode(char **arr, char **bin, char **mask, int bits)
{
	int		size;

	size = ft_strlen(*mask);
	bits--;
	while (bits >= 0)
	{
		if ((*mask)[size] == 'x')
			(*mask)[size] = (*bin)[bits--];
		size--;
	}
	size = 0;
	while ((*mask)[size])
	{
		if ((*mask)[size] == 'x')
			(*mask)[size] = '0';
		size++;
	}
	*arr = ft_split_mask(*mask, size);
	FREE(*mask);
	FREE(*bin);
	return (0);
}

char			*ft_unicode(int unicode)
{
	char	**tab;
	char	*mask;
	char	*bin;
	char	*arr;
	int		bits;

	tab = (char **)malloc(sizeof(char *) * 5);
	mask = NULL;
	tab[0] = "0xxxxxxx";
	tab[1] = "110xxxxx10xxxxxx";
	tab[2] = "1110xxxx10xxxxxx10xxxxxx";
	tab[3] = "11110xxx10xxxxxx10xxxxxx10xxxxxx";
	bin = ft_itoa_base(unicode, 2);
	bits = ft_strlen(bin);
	if (bits <= 7)
		mask = ft_strdup(tab[0]);
	else if (bits > 7 && bits <= 11)
		mask = ft_strdup(tab[1]);
	else if (bits > 11 && bits <= 16)
		mask = ft_strdup(tab[2]);
	else if (bits > 16 && bits <= 21)
		mask = ft_strdup(tab[3]);
	FREE(tab);
	ft_get_unicode(&arr, &bin, &mask, bits);
	return (arr);
}
