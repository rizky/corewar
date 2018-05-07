/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:46:15 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/12 00:51:39 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_wordcounter(const char *str, char c)
{
	int		i;
	int		wcount;
	int		state;

	i = 0;
	wcount = 0;
	state = 0;
	while (str[i])
	{
		if (c == str[i])
			state = 0;
		else if (state == 0)
		{
			state = 1;
			wcount++;
		}
		i++;
	}
	return (wcount);
}

static char
	**ft_word_extractor(const char *str,
	char **strtab, size_t v[4], char c)
{
	while (v[0] <= ft_strlen(str))
	{
		if (c == str[v[0]] || str[v[0]] == '\0')
		{
			if (v[3] == 1)
			{
				strtab[v[1]] = (char*)malloc(sizeof(char) * (v[2] + 1));
				strtab[v[1]] = ft_strncpy(strtab[v[1]],
											str + v[0] - v[2], v[2]);
				strtab[v[1]][v[2]] = '\0';
				v[1]++;
				v[2] = 0;
				v[3] = 0;
			}
		}
		else
		{
			if (v[3] == 0)
				v[3] = 1;
			v[2]++;
		}
		v[0]++;
	}
	strtab[ft_wordcounter(str, c)] = NULL;
	return (strtab);
}

char
	**ft_strsplit(char const *s, char c)
{
	char	**strtab;
	size_t	v[4];

	if (!s)
		return (NULL);
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	v[3] = 0;
	strtab = (char**)malloc(sizeof(*strtab) * (ft_wordcounter(s, c) + 1));
	if (!strtab)
		return (NULL);
	strtab = ft_word_extractor(s, strtab, v, c);
	return (strtab);
}

void
	ft_strtab_free(char **strtab)
{
	int		i;

	i = -1;
	while (strtab[++i] != NULL)
		free(strtab[i]);
	free(strtab);
}
