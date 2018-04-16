/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 09:24:11 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/15 15:47:17 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_asm.h"

int
	asm_check_op(t_asm *a)
{
	int i;

	i = 0;
	if (a->ops[a->op_c].opcode == -1)
		return (ft_error(OP, -1, a->file[a->i]));
	while (i < a->ops[a->op_c].param_c)
	{
		if (a->ops[a->op_c].params[i].type == -1)
			return (ft_error(OP_PARAM, -1, a->file[a->i]));
		i++;
	}
	return (0);
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


int ft_get_name_comment(t_asm *a, header_t *h)
{
	int tmp;
	int j;

	j = 0;
	ft_skip_empty_lines(a);
	if (ft_comment_cmd(a->file[a->i]))
	{
		tmp = ft_get_comment(a, h);
		ft_skip_empty_lines(a);
		a->i++;
	}
	else if (ft_name_cmd(a->file[a->i]))
	{
		tmp = ft_get_name(a, h);
		ft_skip_empty_lines(a);
		a->i++;
	}
	else if (!a->name && !a->comment)
		tmp = ft_error(HEADER, -1, NULL);
	else if (!a->name)
		tmp = ft_error(NAME, -1, NULL);
	else if (!a->comment)
		tmp = ft_error(COMMENT, -1, NULL);
	else
		tmp = ft_error(OTHER, -1, NULL);
	ft_skip_empty_lines(a);
	if (a->name && a->comment && !ft_strchr(LABEL_CHARS, a->file[a->i][0]))
	{
		tmp = ft_printf("Error line %i\n", a->i + 1);
		exit (1);
	}
	return (tmp);
}


int		ft_parsing(t_asm *a, header_t *h)
{
	ft_handle_comments(a->file);
	ft_trim_file(a->file);
//	if (/*ft_get_name(a, h) == -1 || */ft_get_name_comment(a, h) == -1 || ft_get_name_comment(a, h) == -1 )
//		return (-1);
	if (ft_get_name(a, h) == -1)
		return (-1);
	a->i++;
	if (ft_get_comment(a, h) == -1)
		return (-1);
	a->i++;
	ft_check_instructions(a);
	while (a->file[a->i])
	{
		asm_get_op(a);
		if (asm_check_op(a) == -1)
			return (-1);
		a->op_c++;
		a->i++;
	}
	if (asm_populate_indvalue(a) == -1)
		return (-1);
	asm_print(a);
	return (0);
}
