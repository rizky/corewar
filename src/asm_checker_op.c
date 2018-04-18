/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_instructions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 10:22:53 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/18 08:26:11 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"
#include "libft.h"

char *g_opcode[17] =
{
	"live",
	"ld",
	"st",
	"add",
	"sub",
	"and",
	"or",
	"xor",
	"zjmp",
	"ldi",
	"sti",
	"fork",
	"lld",
	"lldi",
	"lfork",
	"aff",
	0
};

int		ft_skip_spaces_tabs(char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int		ft_check_parameters(char *params)
{
	ft_printf("%s\n", params);
	return (0);
}

int		ft_check_opcode2(char *line)
{
	int i;

	i = 0;
	while (g_opcode[i])
	{
		if (ft_strncmp(line, g_opcode[i], ft_strlen(g_opcode[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		ft_check_opcode(t_asm *a)
{
	int i;
	int j;
	int op;

	i = a->i;
	while (a->file[i])
	{
		j = 0;
		ft_skip_empty_lines(a);
		if (ft_is_label(a->file[i])) //label au debut de la ligne
			j = ft_strcspn(a->file[i], ":") + 1;
		j += ft_skip_spaces_tabs(&a->file[i][j]); //va jusqu'a loperation
		if (a->file[i][j])
		{
			if ((op = ft_check_opcode2(&a->file[i][j])) == -1) //check si le debut du test est un op
				return (-1);
			j += ft_strlen(g_opcode[op]) + 1;
			j += ft_skip_spaces_tabs(&a->file[i][j]);
			ft_check_parameters(&a->file[i][j]); //apres lop check les params
		}
		i++;
	}
	return (0);
}

int		ft_check_instructions(t_asm *a)
{
	int start;

	ft_skip_empty_lines(a);
	a->start = a->i;
	if (ft_get_labels(a) == -1 || ft_check_opcode(a) == -1)
	{
		ft_dprintf(2, "Error - invalid instruction\n");
		return (-1);
	}
	if (0)
		ft_print_tab(a->labels);
	ft_free_tab(a->labels, 0);
	return (0);
}
