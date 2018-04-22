/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:38:33 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/22 15:14:47 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

static int
	vm_get_champions(char **av)
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

static int
	vm_print_usage(char **av, int status)
{
	ft_dprintf(2, "usage: %s [-dump nbr_cycles] [-n number] ", av[0]);
	ft_dprintf(2, "champion1.cor ...\n");
	return (status);
}

static int
	vm_binary_toint(char *bin, int size)
{
	int		i;
	int		result;

	i = 1;
	result = 0;
	while (i <= size)
	{
		result += bin[i - 1] << ((size - i) * 8);
		i++;
	}
	return (result);
}

void
	vm_print_verbose(t_vm vm)
{
	ft_printfln("magic: %d", vm.header.magic);
	ft_printfln("name: %s", vm.header.prog_name);
	ft_printfln("size: %d", vm.header.prog_size);
	ft_printfln("comment: %s", vm.header.comment);
	ft_printfln("%*m", vm.header.prog_size, vm.op);
}

static int
	vm_read_binary(int i, char **av, t_vm *vm)
{
	int			fd;
	int			ret;
	char		buf[COMMENT_LENGTH + 4];
	int			op_size;

	if ((fd = open(av[i], O_RDONLY)) == -1)
		return (SOURCEFILE);
	vm->path = av[i];
	if ((ret = read(fd, &buf, 4)) <= 0)
		return (vm_error(INVALID_FILE, -1));
	vm->header.magic = vm_binary_toint(buf, 4);
	if (vm_binary_toint(buf, 4) != -1473805)
		return (vm_error(INVALID_FILE, -1));
	if ((ret = read(fd, &buf, PROG_NAME_LENGTH + 4)) <= 0)
		return (vm_error(INVALID_FILE, -1));
	ft_strncpy(vm->header.prog_name, buf, PROG_NAME_LENGTH + 4 + 1);
	if ((ret = read(fd, &buf, 4) <= 0))
		return (vm_error(INVALID_FILE, -1));
	op_size = vm_binary_toint(buf, 4);
	vm->header.prog_size = op_size;
	if (op_size > CHAMP_MAX_SIZE)
		return (vm_error(CHAMP_MAX, -1));
	if ((ret = read(fd, &buf, COMMENT_LENGTH + 4)) <= 0)
		return (vm_error(INVALID_FILE, -1));
	ft_strncpy(vm->header.comment, buf, COMMENT_LENGTH + 4 + 1);
	if ((ret = read(fd, &buf, op_size)) <= 0)
		return (vm_error(INVALID_FILE, -1));
	vm->op = ft_memalloc(op_size + 1);
	ft_memcpy(vm->op, buf, op_size + 1);
	vm->op[op_size] = '\0';
	close(fd);
	return (0);
}

int
	main(int ac, char **av)
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
	vm_print_verbose(vm);
	return (0);
}
