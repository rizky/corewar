/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:56:36 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/13 15:23:18 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int
	ft_re_matchn(const char* pattern, const char* text, int len)
{
	char	*str;
	int		res;

	res = -1;
	str = ft_memalloc(len + 1);
	ft_memcpy(str, text, len);
	str[len] = '\0';
	res = ft_re_matchp(ft_re_compile(pattern), str);
	free(str);
	return (res);
}

char
	*ft_re_match_capture(const char *pattern, const char *group, const char *text)
{
	int 	len;
	int		start;
	char 	*str;

	if (ft_re_match(pattern, text) == -1)
		return NULL;
	start = ft_re_match(group, text);
	text = text + start;
	len = ft_strlen(text);
	while (ft_re_matchn(group, text, len - 1) == 0)
		len--;
	str = ft_memalloc(len + 1 - 2);
	ft_memcpy(str, text + 1, len - 2);
	str[len] = '\0';
	return (str);
}

int
	ft_get_name(t_asm *a, header_t *h)
{
	ft_skip_empty_lines(a);
	a->name = ft_re_match_capture(".name[ \t]+\"[^\"]+\"$",
				"\".+\"", a->file[a->i]);
	if (a->name == NULL)
		return (ft_error(NAME, -1));
	if (ft_strlen(a->name) > PROG_NAME_LENGTH)
		return (ft_error(NAME_LEN, -1));
	ft_memcpy(h->prog_name, a->name, ft_strlen(a->name) + 1);
	return (0);
}

int
	ft_get_comment(t_asm *a, header_t *h)
{
	ft_skip_empty_lines(a);
	a->comment = ft_re_match_capture(".comment[ \t]+\"[^\"]*\"$",
				"\".*\"", a->file[a->i]);
	if (a->comment == NULL)
		return (ft_error(COMMENT, -1));
	if (ft_strlen(a->comment) > COMMENT_LENGTH)
		return (ft_error(COMMENT_LEN, -1));
	ft_memcpy(h->comment, a->comment, ft_strlen(a->comment) + 1);
	return (0);
}