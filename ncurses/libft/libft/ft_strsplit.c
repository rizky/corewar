/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 07:22:37 by jyeo              #+#    #+#             */
/*   Updated: 2017/11/16 02:49:05 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_len(const char *str, char c)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			len++;
		i++;
	}
	return (len);
}

static int		get_len2(const char *str, char c)
{
	int len;

	len = 0;
	while (*str)
	{
		if (*str != c)
			len++;
		else
			return (len);
		str++;
	}
	return (len);
}

static char		*fill_words(const char *s, char c, int size)
{
	int		i;
	char	*new;

	i = 0;
	if ((new = ft_strnew(size)) == NULL)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		size;
	int		size_2;
	char	**new;

	i = 0;
	if (!s || !c)
		return (NULL);
	size = get_len(s, c);
	if ((new = (char **)malloc(sizeof(char *) * (size + 1))) == NULL)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			size_2 = get_len2(s, c);
			new[i] = fill_words(s, c, size_2);
			i++;
			s = s + size_2;
		}
	}
	new[i] = 0;
	return (new);
}
