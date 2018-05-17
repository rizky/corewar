/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_match_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:22:11 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/21 11:51:04 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_re.h"

int
	ft_re_match(const char *pattern, const char *text)
{
	if (!text)
		return (-1);
	return (ft_re_matchp(ft_re_compile(pattern), text));
}

int
	ft_re_matchp(t_re pattern, const char *text)
{
	int idx;

	if (!text)
		return (-1);
	if (pattern != 0)
	{
		if (pattern[0].type == BEGIN)
			return ((matchpattern(&pattern[1], text)) ? 0 : -1);
		else
		{
			idx = -1;
			while (*text != '\0')
			{
				idx += 1;
				if (matchpattern(pattern, text))
					return (idx);
				text++;
			}
		}
	}
	return (-1);
}

int
	matchplus(t_regex p, t_regex *pattern, const char *text)
{
	while ((text[0] != '\0') && matchone(p, *text++))
		if (matchpattern(pattern, text))
			return (1);
	return (0);
}

int
	matchquestion(t_regex p, t_regex *pattern, const char *text)
{
	if (matchone(*pattern, *text) || matchone(p, *text++))
		return (matchpattern(pattern, text));
	return (0);
}

int
	matchpattern(t_regex *pattern, const char *text)
{
	while (1)
	{
		if (pattern[0].type == UNUSED)
			return (matchunused(pattern[1], &pattern[2], text));
		else if (pattern[1].type == QUESTIONMARK)
			return (matchquestion(pattern[0], &pattern[2], text));
		else if (pattern[1].type == STAR)
			return (matchstar(pattern[0], &pattern[2], text));
		else if (pattern[1].type == PLUS)
			return (matchplus(pattern[0], &pattern[2], text));
		else if ((pattern[0].type == END) && pattern[1].type == UNUSED)
			return (text[0] == '\0');
		if (!(text[0] != '\0' && matchone(*pattern++, *text++)))
			break ;
	}
	return (0);
}
