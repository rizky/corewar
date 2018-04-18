/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helper_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:57:53 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/18 14:54:24 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"
#include "libft.h"

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

static int	ft_skip_header(char **file)
{
	int		i;
	int		j;
	int		quotes;
	char	*tmp;

	i = -1;
	quotes = 0;
	while (file[++i])
	{
		j = -1;
		if (ft_strstr(file[i], NAME_CMD_STRING) ||
			ft_strstr(file[i], COMMENT_CMD_STRING))
		{
			tmp = ft_strdup(ft_strchr(file[i], '.'));
			free(file[i]);
			file[i] = tmp;
		}
		while (file[i][++j])
			(file[i][j] == '\"') ? quotes++ : 0;
		if (quotes == 4)
			return (i + 1);
	}
	return (0);
}

void		ft_trim_file(char **file)
{
	int		i;
	char	*tmp;

	i = ft_skip_header(file);
	while (file[i])
	{
		tmp = ft_strtrim(file[i]);
		free(file[i]);
		file[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
}
