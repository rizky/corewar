/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:59:42 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/16 11:39:46 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

/*
** Always tries to use the last argument
** Only accepts files with filename extension .s
*/

static int	ft_read_sourcefile(int i, char **av, t_asm *a)
{
	int		fd;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*file[2];

	if ((fd = open(av[i], O_RDONLY)) == -1)
		return (SOURCEFILE);
	a->path = av[i];
	file[0] = ft_strnew(0);
	while ((ret = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		file[1] = file[0];
		file[0] = ft_strjoin(file[1], buf);
		free(file[1]);
	}
	close(fd);
	if (ft_file_is_empty(file[0]))
		return (ft_free(file[0], EMPTY));
	if (file[0][ft_strlen(file[0]) - 1] != '\n')
		return (ft_free(file[0], NEWLINE));
	if ((a->file = ft_strsplit(file[0], '\n')) == NULL)
		return (ft_free(file[0], MALLOC));
	free(file[0]);
	return (0);
}

static int	ft_filename_extension(char *file)
{
	if (file[ft_strlen(file) - 1] == 's' && file[ft_strlen(file) - 2] == '.')
		return (1);
	return (0);
}

static int	ft_init(int ac, char **av, t_asm *a)
{
	int errnum;
	int	i;

	ft_bzero(a, sizeof(t_asm));
	i = asm_getoptions(av, a->opt);
	i = (a->opt[OPT_M]) ? i: ac - 1;
	while (i < ac)
	{
		if (ac < 2 || !ft_filename_extension(av[i]))
		{
			ft_dprintf(2, "Usage: %s <sourcefile.s>\n", av[0]);
			return (-1);
		}
		if ((errnum = ft_read_sourcefile(i, av, a)) > 0)
		{
			if (errnum == SOURCEFILE)
				ft_dprintf(2, "Can't read source file %s\n", av[i]);
			else
				return (ft_error(errnum, -1, NULL));
			return (-1);
		}
		i++;
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_asm		a;
	t_array		ops;

	if (ft_init(ac, av, &a) == -1)
		return (-1);
	ops = NEW_ARRAY(t_op);
	a.ops = &ops;
	if (ft_parsing(&a) == -1)
		return (ft_free_asm(&a, -1));
	if (a.opt[OPT_A])
		asm_print(a);
	else
		asm_compiler(a);
	ft_free_asm(&a, 0);
	return (0);
}
