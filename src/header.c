/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:56:36 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/11 14:57:12 by fpetras          ###   ########.fr       */
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

int			ft_get_comment(t_asm *a)
{
	a->i++;
	ft_skip_empty_lines(a);
	if (!ft_comment_cmd(a->file[a->i]) || !ft_quotes(a->file[a->i]))
		return (ft_error(COMMENT, -1));
	a->comment = &a->file[a->i][ft_strcspn(a->file[a->i], "\"") + 1];
	return (0);
}

int			ft_get_name(t_asm *a)
{
	ft_skip_empty_lines(a);
	if (!ft_name_cmd(a->file[a->i]) || !ft_quotes(a->file[a->i]))
		return (ft_error(NAME, -1));
	a->name = &a->file[a->i][ft_strcspn(a->file[a->i], "\"") + 1];
	return (0);
}
