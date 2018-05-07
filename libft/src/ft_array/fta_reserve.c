/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fta_reserve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 20:10:30 by rnugroho          #+#    #+#             */
/*   Updated: 2018/02/17 11:22:41 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

/*
** Array::reserve
** -
** When one has an estimation of the number of elements that they will add
** to the array, using reserve will prevent multiple re-allocations,
** and ensure the best complexity.
** Indeed this function makes sure that the array has enough room
** for _size_ elements to be added.
** -
** _size_ is the number of elements that are planned to be added.
** -
** Returns a status :
** 0 in case of success,
** 1 if a re-alloc failed, and leaves the array as-is.
*/

int		fta_reserve(t_array *self, size_t size)
{
	const size_t	total_size = size + self->size;
	size_t			new_size;

	if (total_size > self->max)
	{
		new_size = (self->max > 0 ? self->max : ARRAY_INITIAL_SIZE);
		while (new_size < total_size)
			new_size *= ARRAY_FACTOR;
		return (fta_resize(self, new_size));
	}
	return (0);
}
