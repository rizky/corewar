/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:59:42 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/12 08:36:14 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Always tries to use the last argument
** Only accepts files with filename extension .s
*/

static char	**ft_read_sourcefile(int ac, char **av)
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

static int	ft_filename_extension(char *file)
{
	if (file[ft_strlen(file) - 1] != 's' && file[ft_strlen(file) - 2] != '.')
		return (0);
	return (1);
}

static int	ft_init(int ac, char **av, t_asm *a, header_t *h)
{
	ft_bzero(a, sizeof(t_asm));
	ft_bzero(h, sizeof(header_t));
	if (ac < 2 || !ft_filename_extension(av[ac - 1]))
	{
		ft_dprintf(2, "Usage: %s <sourcefile.s>\n", av[0]);
		return (-1);
	}
	if ((a->file = ft_read_sourcefile(ac, av)) == NULL)
	{
		ft_dprintf(2, "Can't read source file %s\n", av[ac - 1]);
		return (-1);
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_asm		a;
	header_t	h;

	if (ft_init(ac, av, &a, &h) == -1)
		return (-1);
	if (ft_parsing(&a, &h) == -1)
		return (ft_free_tab(a.file, -1));
//	ft_compilation();
//	ft_print_tab(a.file);
	ft_free_tab(a.file, 0);
	return (0);
}
