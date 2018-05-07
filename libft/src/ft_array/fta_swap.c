/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fta_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 18:06:01 by rnugroho          #+#    #+#             */
/*   Updated: 2018/02/17 11:23:11 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"
#include "libft.h"

/*
** Array::_swap
** -
** swaps an array segment with what follows.
** very specific function, not useful for standard cases.
** -
** "   -1415920000"
** -swap(4, 10)->
** "   -0000141592"
** -swap(0, 4)->
** "-0000141592   "
*/

void	ft_exit(char const *const fnc, char const *const str)
{
	ft_putstr_fd("ERROR\tCritical failure in function ", 2);
	ft_putstr_fd(fnc, 2);
	ft_putstr_fd(". The program will exit, reason being : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(".\n", 2);
	exit(1);
}

void	*ft_safe_calloc(size_t count, size_t size)
{
	void	*const ans = malloc(count * size);

	if (ans == NULL)
		ft_exit("ft_safe_calloc", "Out of memory (Malloc failed)");
	ft_bzero(ans, count * size);
	return (ans);
}

void	fta_swap(t_array *self, size_t before, size_t after)
{
	char			*tmp;
	const size_t	len = after - before;
	const size_t	m = self->type_size;

	tmp = ft_safe_calloc(len, m);
	ft_memcpy(tmp, self->data + before * m, m * len);
	ft_memmove(self->data + before * m, self->data + after * m,
		(self->size - after) * m);
	ft_memcpy(self->data + (self->size - len) * m, tmp, len * m);
	free(tmp);
}
