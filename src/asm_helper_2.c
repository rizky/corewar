/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helper_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:57:53 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/17 12:28:19 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

static int	ft_inside_quotes(char *line, int j)
{
	int i;
	int quotes;
	int inside;

	i = 0;
	quotes = 0;
	inside = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			quotes++;
		if (i == j && quotes == 1)
			inside = 1;
		i++;
	}
	if (quotes == 2 && inside == 1)
		return (1);
	return (0);
}

void		ft_handle_comments(char **file)
{
	int i;
	int j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (file[i][j] == COMMENT_CHAR || file[i][j] == ';')
			{
				if ((ft_strstr(file[i], NAME_CMD_STRING) ||
					ft_strstr(file[i], COMMENT_CMD_STRING)) &&
					ft_inside_quotes(file[i], j))
					;
				else
					file[i][j] = '\0';
			}
			j++;
		}
		i++;
	}
}

void		ft_trim_file(char **file)
{
	int		i;
	char	*tmp;

	i = 0;
	while (file[i])
	{
		tmp = ft_strtrim(file[i]);
		free(file[i]);
		file[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
}
