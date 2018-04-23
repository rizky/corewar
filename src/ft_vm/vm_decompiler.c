/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_decompiler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 20:42:42 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/23 23:14:31 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

int
	vm_binary_toint(unsigned char *bin, int size)
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

int
	vm_read_magic(int fd, t_champ *champ)
{
	int				ret;
	unsigned char	buf[COMMENT_LENGTH + 4];

	if ((ret = read(fd, &buf, 4)) <= 0)
		return (vm_error(INVALID_FILE, -1));
	champ->header.magic = vm_binary_toint(buf, 4);
	if (vm_binary_toint(buf, 4) != COREWAR_EXEC_MAGIC)
		return (vm_error(INVALID_FILE, -1));
	return (0);
}

int
	vm_read_header(int fd, t_champ *champ)
{
	int				ret;
	unsigned char	buf[COMMENT_LENGTH + 4];

	if (vm_read_magic(fd, champ) == -1)
		return (-1);
	if ((ret = read(fd, &buf, PROG_NAME_LENGTH + 4)) <= 0)
		return (vm_error(INVALID_FILE, -1));
	ft_strncpy(champ->header.prog_name, (char*)buf, PROG_NAME_LENGTH + 4 + 1);
	if ((ret = read(fd, &buf, 4) <= 0))
		return (vm_error(INVALID_FILE, -1));
	champ->header.prog_size = vm_binary_toint(buf, 4);
	if (champ->header.prog_size > CHAMP_MAX_SIZE)
		return (vm_error(CODE_MAX, -1));
	if ((ret = read(fd, &buf, COMMENT_LENGTH + 4)) <= 0)
		return (vm_error(INVALID_FILE, -1));
	ft_strncpy(champ->header.comment, (char*)buf, COMMENT_LENGTH + 4 + 1);
	return (0);
}

int
	vm_handle_n(int i, char **av, int *index)
{
	if (ft_strcmp(av[i], "-n") == 0)
	{
		if (!av[i + 1] || ft_atoi(av[i + 1]) == 0)
			return (-1);
		i++;
		*index = ft_atoi(av[i]) - 1;
		if (*index < 0 || *index > 3)
			return (-1);
		i++;
	}
	return (i);
}

int
	vm_read_binary(int i, char **paths, t_vm *vm)
{
	int				fd;
	int				ret;
	unsigned char	buf[COMMENT_LENGTH + 4];
	t_champ			champ;

	if ((fd = open(paths[i], O_RDONLY)) == -1)
		return (vm_error(INVALID_FILE, -1));
	if (vm_read_header(fd, &champ) == -1)
		return (-1);
	if ((ret = read(fd, &buf, champ.header.prog_size)) <= 0)
		return (vm_error(INVALID_FILE, -1));
	champ.op = ft_memalloc(champ.header.prog_size + 1);
	ft_memcpy(champ.op, buf, champ.header.prog_size + 1);
	champ.op[champ.header.prog_size] = '\0';
	vm->champ[i] = champ;
	vm->champ[i].processes = fta_alloc(sizeof(t_process));
	close(fd);
	return (i);
}
