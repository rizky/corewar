/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:38:33 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/22 13:39:03 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

static int	vm_get_champions(char **av)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while (av[++i])
	{
		if (ft_strequ(&av[i][ft_strlen(av[i]) - 4], ".cor"))
			num++;
	}
	return (num);
}

static int	vm_print_usage(char **av, int status)
{
	ft_dprintf(2, "usage: %s [-dump nbr_cycles] [-n number] ", av[0]);
	ft_dprintf(2, "champion1.cor ...\n");
	return (status);
}

static int	vm_read_binary(int i, char **av, t_vm *vm)
{
	int		fd;
	int		ret;
	char	buf[COMMENT_LENGTH + 4];

	if ((fd = open(av[i], O_RDONLY)) == -1)
		return (SOURCEFILE);
	vm->path = av[i];
	if ((ret = read(fd, &buf, 4)) > 0)
		ft_printfln("%4m", buf);
	if ((ret = read(fd, &buf, PROG_NAME_LENGTH + 4)) > 0)
		ft_printfln("%*m", ft_strlen(buf), buf);
	if ((ret = read(fd, &buf, 4) > 0))
		ft_printfln("%4m", buf);
	if ((ret = read(fd, &buf, COMMENT_LENGTH + 4)) > 0)
		ft_printfln("%*m", ft_strlen(buf), buf);
	close(fd);
	return (0);
}

int			main(int ac, char **av)
{
	t_vm	vm;

	ft_bzero(&vm, sizeof(t_vm));
	if (ac < 2 || vm_options(av, &vm) == -1)
		return (vm_print_usage(av, -1));
	else if (vm_get_champions(av) > MAX_PLAYERS)
	{
		ft_dprintf(2, "Too many champions\n");
		return (-1);
	}
	vm_read_binary(1, av, &vm);
	vm_print(vm);
	return (0);
}
