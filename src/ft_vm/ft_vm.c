/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:38:33 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/22 20:29:33 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

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

static int
	vm_read_binary(int i, char **av, t_vm *vm)
{
	int			fd;
	int			ret;
	char		buf[COMMENT_LENGTH + 4];
	int			op_size;
	t_champ		champ;

	if (!ft_strequ(&av[i][ft_strlen(av[i]) - 4], ".cor") ||
		(fd = open(av[i], O_RDONLY)) == -1)
		return (vm_error(INVALID_FILE, -1));
	champ.path = av[i];
	if ((ret = read(fd, &buf, 4)) <= 0)
		return (vm_error(INVALID_FILE, -1));
	champ.header.magic = vm_binary_toint(buf, 4);
	if (vm_binary_toint(buf, 4) != -1473805)
		return (vm_error(INVALID_FILE, -1));
	if ((ret = read(fd, &buf, PROG_NAME_LENGTH + 4)) <= 0)
		return (vm_error(INVALID_FILE, -1));
	ft_strncpy(champ.header.prog_name, buf, PROG_NAME_LENGTH + 4 + 1);
	if ((ret = read(fd, &buf, 4) <= 0))
		return (vm_error(INVALID_FILE, -1));
	op_size = vm_binary_toint(buf, 4);
	champ.header.prog_size = op_size;
	if (op_size > CHAMP_MAX_SIZE)
		return (vm_error(CODE_MAX, -1));
	if ((ret = read(fd, &buf, COMMENT_LENGTH + 4)) <= 0)
		return (vm_error(INVALID_FILE, -1));
	ft_strncpy(champ.header.comment, buf, COMMENT_LENGTH + 4 + 1);
	if ((ret = read(fd, &buf, op_size)) <= 0)
		return (vm_error(INVALID_FILE, -1));
	champ.op = ft_memalloc(op_size + 1);
	ft_memcpy(champ.op, buf, op_size + 1);
	champ.op[op_size] = '\0';
	vm->champ[vm->champ_size] = champ;
	vm->champ_size++;
	close(fd);
	return (0);
}

static
	vm_print_memory(char memory[MEM_SIZE])
{

}

int
	main(int ac, char **av)
{
	t_vm			vm;
	int				i;
	static	int		opt[OPT_NUM] = {0, 1};
	char			memory[MEM_SIZE];

	if ((i = vm_getoptions(av, opt)) == -1)
		return (vm_print_usage(av, -1));
	ft_bzero(&vm, sizeof(t_vm));
	if (opt[OPT_N] > 4)
		return (vm_error(CHAMP_MAX, -1));
	while (opt[OPT_N] > 0 || i < ac)
	{
		if (i >= ac || opt[OPT_N] == 0)
			return (vm_print_usage(av, -1));
		vm_read_binary(i, av, &vm);
		i++;
		opt[OPT_N]--;
	}
	i = -1;
	while (++i < vm.champ_size)
		vm_print_verbose(vm, i);
	return (0);
}
