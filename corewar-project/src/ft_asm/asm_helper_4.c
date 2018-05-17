/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helper_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:46:15 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/07 18:24:49 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

/*
** Retains multiple empty lines
** Necessary to handle multi-line name or comment
*/

int
	asm_wordcounter(const char *str, char c)
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
			wcount++;
		i++;
	}
	wcount++;
	return (wcount);
}

static char
	**asm_word_extractor(const char *str, char **strtab, size_t v[4], char c)
{
	while (v[0] <= ft_strlen(str))
	{
		if (c == str[v[0]] || str[v[0]] == '\0')
		{
			if (!(strtab[v[1]] = (char*)malloc(sizeof(char) * (v[2] + 1))))
			{
				ft_free_strtab(strtab, 0);
				return (NULL);
			}
			strtab[v[1]] = ft_strncpy(strtab[v[1]],
										str + v[0] - v[2], v[2]);
			strtab[v[1]][v[2]] = '\0';
			v[1]++;
			v[2] = 0;
			v[3] = 0;
		}
		else
		{
			(v[3] == 0) ? v[3] = 1 : 0;
			v[2]++;
		}
		v[0]++;
	}
	strtab[asm_wordcounter(str, c)] = NULL;
	return (strtab);
}

char
	**asm_strsplit(char const *s, char c)
{
	char	**strtab;
	size_t	v[4];

	if (!s)
		return (NULL);
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	v[3] = 0;
	strtab = (char**)malloc(sizeof(*strtab) * (asm_wordcounter(s, c) + 1));
	if (!strtab)
		return (NULL);
	strtab = asm_word_extractor(s, strtab, v, c);
	return (strtab);
}
