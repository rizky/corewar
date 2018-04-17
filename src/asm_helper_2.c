/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helper_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:57:53 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/17 11:58:41 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

void	ft_handle_comments(char **file)
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
				file[i][j] = '\0';
			j++;
		}
		i++;
	}
}

void	ft_trim_file(char **file)
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
