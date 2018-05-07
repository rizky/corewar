/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:22:05 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/21 12:13:10 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_re.h"

static t_regex	g_re_compiled[MAX_REGEXP_OBJECTS];

static void
	compile_slash(char pattern, int j)
{
	if (pattern == 'd')
		g_re_compiled[j].type = DIGIT;
	else if (pattern == 'D')
		g_re_compiled[j].type = NOT_DIGIT;
	else if (pattern == 'w')
		g_re_compiled[j].type = ALPHA;
	else if (pattern == 'W')
		g_re_compiled[j].type = NOT_ALPHA;
	else if (pattern == 's')
		g_re_compiled[j].type = WHITESPACE;
	else if (pattern == 'S')
		g_re_compiled[j].type = NOT_WHITESPACE;
	else
	{
		g_re_compiled[j].type = CHAR;
		g_re_compiled[j].t_char.ch = pattern;
	}
}

static int
	compile_sq_bracket(const char *pattern, int *ccl_bufidx, int *i, int j)
{
	static unsigned char	ccl_buf[MAX_CHAR_CLASS_LEN];
	int						buf_begin;

	buf_begin = (*ccl_bufidx);
	if (pattern[(*i) + 1] == '^')
	{
		g_re_compiled[j].type = INV_CHAR_CLASS;
		(*i)++;
	}
	else
		g_re_compiled[j].type = CHAR_CLASS;
	while ((pattern[(*i)] != ']')
			&& (pattern[(*i) + 1] != '\0'))
	{
		(*i)++;
		if ((*ccl_bufidx) >= MAX_CHAR_CLASS_LEN)
			return (0);
		ccl_buf[(*ccl_bufidx)++] = pattern[(*i)];
	}
	if ((*ccl_bufidx) >= MAX_CHAR_CLASS_LEN)
		return (0);
	ccl_buf[(*ccl_bufidx)++] = (0);
	g_re_compiled[j].t_char.ccl = &ccl_buf[buf_begin];
	return (1);
}

static int
	compile_simple_symbols(char c, int j)
{
	if (c == '^')
		g_re_compiled[j].type = BEGIN;
	else if (c == '$')
		g_re_compiled[j].type = END;
	else if (c == '.')
		g_re_compiled[j].type = DOT;
	else if (c == '*')
		g_re_compiled[j].type = STAR;
	else if (c == '+')
		g_re_compiled[j].type = PLUS;
	else if (c == '?')
		g_re_compiled[j].type = QUESTIONMARK;
	else
		return (0);
	return (1);
}

t_re
	ft_re_compile(const char *pattern)
{
	int		ccl_bufidx;
	char	c;
	int		i;
	int		j;

	ccl_bufidx = 1;
	i = -1;
	j = -1;
	while (pattern[++i] != '\0' && (++j + 1 < MAX_REGEXP_OBJECTS))
	{
		c = pattern[i];
		if (compile_simple_symbols(c, j))
			(void)0;
		else if (c == '\\')
			(pattern[i + 1] != '\0') ? compile_slash(pattern[++i], j) : 0;
		else if (c == '[' && !compile_sq_bracket(pattern, &ccl_bufidx, &i, j))
			return (0);
		else if (c != '[')
		{
			g_re_compiled[j].type = CHAR;
			g_re_compiled[j].t_char.ch = c;
		}
	}
	g_re_compiled[j + 1].type = UNUSED;
	return ((t_re)g_re_compiled);
}
