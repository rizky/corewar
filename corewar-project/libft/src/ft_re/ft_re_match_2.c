/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_match_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:22:19 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/21 12:15:00 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_re.h"

int
	ismetachar(char c)
{
	return ((c == 's') || (c == 'S') == (c == 'w')
			|| (c == 'W') || (c == 'd') || (c == 'D'));
}

int
	matchmetachar(char c, const char *str)
{
	if (str[0] == 'd')
		return (matchdigit(c));
	if (str[0] == 'D')
		return (!matchdigit(c));
	if (str[0] == 'w')
		return (matchalphanum(c));
	if (str[0] == 'W')
		return (!matchalphanum(c));
	if (str[0] == 's')
		return (matchwhitespace(c));
	if (str[0] == 'S')
		return (!matchwhitespace(c));
	return (c == str[0]);
}

int
	matchcharclass(char c, const char *str)
{
	while (*str != '\0' && *str != ']')
	{
		if (matchrange(c, str))
			return (1);
		else if (str[0] == '\\')
		{
			str += 1;
			if (matchmetachar(c, str))
				return (1);
			else if ((c == str[0]) && !ismetachar(c))
				return (1);
		}
		else if (c == str[0])
		{
			if (c == '-')
				return ((str[-1] == '\0') || (str[1] == '\0'));
			else
				return (1);
		}
		str++;
	}
	return (0);
}

int
	matchone(t_regex p, char c)
{
	if (p.type == DOT)
		return (1);
	if (p.type == CHAR_CLASS)
		return (matchcharclass(c, (const char*)p.t_char.ccl));
	if (p.type == INV_CHAR_CLASS)
		return (!matchcharclass(c, (const char*)p.t_char.ccl));
	if (p.type == DIGIT)
		return (matchdigit(c));
	if (p.type == NOT_DIGIT)
		return (!matchdigit(c));
	if (p.type == ALPHA)
		return (matchalphanum(c));
	if (p.type == NOT_ALPHA)
		return (!matchalphanum(c));
	if (p.type == WHITESPACE)
		return (matchwhitespace(c));
	if (p.type == NOT_WHITESPACE)
		return (!matchwhitespace(c));
	return (p.t_char.ch == c);
}

int
	matchstar(t_regex p, t_regex *pattern, const char *text)
{
	while (1)
	{
		if (matchpattern(pattern, text))
			return (1);
		if (!((text[0] != '\0') && matchone(p, *text++)))
			break ;
	}
	return (0);
}
