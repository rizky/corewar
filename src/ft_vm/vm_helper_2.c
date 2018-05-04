/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_helper_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:28:03 by fpetras           #+#    #+#             */
/*   Updated: 2018/05/04 14:21:48 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void
	vm_init_g_var(void)
{
	g_cycles = 0;
	g_cycles_to = 0;
	g_cycles_to_die = CYCLE_TO_DIE;
	g_live_nbr = 0;
	ft_bzero(&g_memory, MEM_SIZE);
	ft_bzero(&g_memory_mark, MEM_SIZE);
}

char
	*vm_to_big_endian(int value, int size)
{
	t_array	result;
	int		i;
	int		bits;

	i = 0;
	result = NEW_ARRAY(char);
	bits = size * 8;
	while (i <= bits - 8)
	{
		fta_append_char(&result, value >> (bits - 8 - i));
		i = i + 8;
	}
	return (result.data);
}

void
	*vm_memmark(void *dst, int i, size_t n)
{
	unsigned char *dst_p;

	dst_p = (unsigned char*)dst;
	while (n-- > 0)
		*dst_p++ = i;
	return (dst);
}

void
	vm_st_mem(int index, char *value, int champ, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (index == MEM_SIZE)
			index = 0;
		g_memory[index] = value[i];
		g_memory_mark[index] = champ + 1;
		index++;
		i++;
	}
}

int
	vm_ld_mem(int index, int size)
{
	int		i;
	int		result;
	int		max;

	i = 1;
	result = 0;
	max = 0;
	while (i <= size)
	{
		if (index == MEM_SIZE)
			index = 0;
		result += g_memory[index] << ((size - i) * 8);
		max += 0xff << ((i - 1) * 8);
		i++;
		index++;
	}
	if (result > max / 2 + 1)
		result = result - (max + 1);
	return (result);
}
