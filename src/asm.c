/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:59:42 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/10 15:27:47 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Always tries to use the last argument
** Only accepts files with filename extension .s
*/

char	**ft_read_sourcefile(int ac, char **av)
{
	int		fd;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*file[2];
	char	**sourcefile;

	if ((fd = open(av[ac - 1], O_RDONLY)) == -1)
		return (NULL);
	file[0] = ft_strnew(0);
	while ((ret = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		file[1] = file[0];
		file[0] = ft_strjoin(file[1], buf);
		free(file[1]);
	}
	close(fd);
	sourcefile = ft_strsplit(file[0], '\n');
	free(file[0]);
	return (sourcefile);
}

int		ft_filename_extension(char *file)
{
	if (file[ft_strlen(file) - 1] != 's' && file[ft_strlen(file) - 2] != '.')
		return (0);
	return (1);
}

int		ft_init(int ac, char **av, t_asm *a)
{
	if (ac < 2 || !ft_filename_extension(av[ac - 1]))
	{
		ft_dprintf(2, "Usage: %s <sourcefile.s>\n", av[0]);
		return (-1);
	}
	if ((a->sourcefile = ft_read_sourcefile(ac, av)) == NULL)
	{
		ft_dprintf(2, "Can't read source file %s\n", av[ac - 1]);
		return (-1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_asm a;

	if (ft_init(ac, av, &a) == -1)
		return (-1);
	ft_print_tab(a.sourcefile);
	ft_free_tab(a.sourcefile);
	return (0);
}
