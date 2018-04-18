/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:59:42 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/18 09:14:28 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"
//#include "libft.h"

/*
** Always tries to use the last argument
** Only accepts files with filename extension .s
*/

static int	ft_end_of_input(char *file)
{
	int		i;
	char	comment[2];
	char	*line;

	if (file[ft_strlen(file) - 1] != '\n')
	{
		i = 0;
		comment[0] = COMMENT_CHAR;
		comment[1] = '\0';
		line = ft_strrchr(file, '\n') + 1;
		line[ft_strcspn(line, comment)] = '\0';
		line[ft_strcspn(line, ";")] = '\0';
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] != '\0')
			return (1);
	}
	return (0);
}

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
	if (ft_end_of_input(file[0]))
		return (ft_free(file[0], NEWLINE));
	if ((a->file = ft_strsplit_keep_empty(file[0], '\n')) == NULL)
		return (ft_free(file[0], MALLOC));
	free(file[0]);
	return (0);
}

static int	ft_init(int ac, char **av, t_asm *a, int i)
{
	int errnum;

	ft_bzero(a, sizeof(t_asm));
	if (ac < 2 || !ft_filename_extension(av[i]))
	{
		ft_dprintf(2, "usage: %s [-a] sourcefile.s\n", av[0]);
		ft_dprintf(2, "       %s [-a] [-m] sourcefile.s ...\n", av[0]);
		ft_dprintf(2, "    -a : Prints a stripped and annotated version");
		ft_dprintf(2, " of the code\n");
		ft_dprintf(2, "    -m : Allows processing of multiple files\n");
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
	return (0);
}

static int	asm_getoptions(char **av, int opt[OPT_NUM])
{
	int			i;
	int			j;
	const char	*c_opt = OPT_STR;
	int			c;

	c = 0;
	ft_bzero(opt, 2 * sizeof(int));
	i = 0;
	while (av[++i] && av[i][0] == '-')
	{
		j = 0;
		while (av[i][++j])
			if ((c = is_in(av[i][j], c_opt)) != -1)
				opt[c] = 1;
			else
				return (i);
	}
	return (i);
}

int			main(int ac, char **av)
{
	t_asm	a;
	t_array	ops;
	int		i;
	int		opt[OPT_NUM];

	i = asm_getoptions(av, opt);
	i = (opt[OPT_M]) ? i : ac - 1;
	while (i < ac)
	{
		(opt[OPT_M] && i > asm_getoptions(av, opt)) ? ft_printf("\n") : 0;
		opt[OPT_M] ? ft_printf("\t%*w%s%w\n", 3, av[i]) : 0;
		if (ft_init(ac, av, &a, i) == -1)
			return (-1);
		ops = NEW_ARRAY(t_op);
		a.ops = &ops;
		if (ft_parsing(&a) == -1)
			return (ft_free_asm(&a, -1));
		if (opt[OPT_A])
			asm_print(a);
		else
			asm_compiler(a);
		ft_free_asm(&a, 0);
		i++;
	}
	return (0);
}
