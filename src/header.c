/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:56:36 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/13 14:41:24 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_quotes(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i] && count != 2)
	{
		if (line[i] == '\"')
		{
			count++;
			line[i] = (count == 2) ? '\0' : line[i];
		}
		i++;
	}
	if (count == 2)
		while (line[i])
		{
			if (!ft_isspace(line[i]))
				return (0);
			i++;
		}
	return (count == 2);
}

static int	ft_name_cmd(char *line)
{
	if (!ft_strnequ(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) ||
		(!ft_isspace(line[ft_strlen(NAME_CMD_STRING)]) &&
		line[ft_strlen(NAME_CMD_STRING)] != '\"'))
		return (0);
	return (1);
}

static int	ft_comment_cmd(char *line)
{
	if (!ft_strnequ(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) ||
		(!ft_isspace(line[ft_strlen(COMMENT_CMD_STRING)]) &&
		line[ft_strlen(COMMENT_CMD_STRING)] != '\"'))
		return (0);
	return (1);
}

int			ft_get_comment(t_asm *a, header_t *h)
{
	a->i++;
	ft_skip_empty_lines(a);
	if (!ft_comment_cmd(a->file[a->i]) || !ft_quotes(a->file[a->i]))
		return (ft_error(COMMENT, -1));
	a->comment = &a->file[a->i][ft_strcspn(a->file[a->i], "\"") + 1];
	if (ft_strlen(a->comment) > COMMENT_LENGTH)
		return (ft_error(COMMENT_LEN, -1));
	ft_memcpy(h->comment, a->comment, ft_strlen(a->comment) + 1);
	return (0);
}

int
	ft_re_matchn(const char* pattern, const char* text, int len)
{
	char	*str;
	int		res;

	res = -1;
	str = ft_memalloc(len);
	ft_memcpy(str, text, len);
	str[len] = '\0';
	ft_printfln("%s", str);
	res = ft_re_matchp(ft_re_compile(pattern), str);
	return (res);
}

char
	*ft_re_match_group(const char *pattern, const char *group, const char *text)
{
	int 	len;
	int		start;
	t_array str;

	if (ft_re_match(pattern, text) == -1)
		return NULL;
	start = ft_re_match(group, text);
	text = text + start;
	len = ft_strlen(text);
	while (ft_re_matchn(group, text, len - 1) == 0)
		len--;
	str = NEW_ARRAY(char);
	fta_reserve(&str, len);
	ft_strncpy(str.data, text, len);
	return (str.data);
}
int			ft_get_name(t_asm *a, header_t *h)
{
	ft_skip_empty_lines(a);
	a->name = ft_re_match_group(".name[ \t]+\".+\"$", "\".+\"",a->file[a->i]);
	if (a->name == NULL)
		return (ft_error(NAME, -1));
	if (ft_strlen(a->name) > PROG_NAME_LENGTH)
		return (ft_error(NAME_LEN, -1));
	ft_memcpy(h->prog_name, a->name, ft_strlen(a->name) + 1);
	return (0);
}
