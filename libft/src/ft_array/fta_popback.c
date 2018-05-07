/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fta_popback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 20:08:29 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/01 00:22:37 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"
#include "libft.h"

/*
** Array::pop_back
** -
** Removes at most _len_ elements at the end.
** -
** _len_ is the number of elements to be removed.
*/

void
	fta_popback(t_array *self, size_t len)
{
	self->size -= _MIN2(len, self->size);
}

/*
** Array::pop_back w/ function
** -
** Same as pop_back, but provides a way to avoid leaks by freeing
** contents pointed by the poped elements.
** -
** _len_ is the number of elements to be removed.
** _del_ is a function that knows how to properly free a single element's
** contents from its address.
*/

void
	fta_popbackf(t_array *self, size_t len, void (*del)(void *))
{
	while (self->size > 0 && len > 0)
	{
		self->size--;
		del(ARRAY_END(self));
		len--;
	}
}

void
	fta_popzero(t_array *self, int *ans)
{
	while (((ARRAY_LAST(self))[0] == '0' &&
		(ft_isdigit((ARRAY_LAST(self) - 1)[0]) ||
		(ARRAY_LAST(self) - 1)[0] == '.')) ||
		(ARRAY_LAST(self))[0] == '.')
	{
		fta_popback(self, 1);
		ans--;
	}
}

void
	fta_popzerohex(t_array *d, int *ans)
{
	while (((ARRAY_LAST(d))[0] == '0' &&
		(ft_ishexdigit((ARRAY_LAST(d) - 1)[0]) ||
		(ARRAY_LAST(d) - 1)[0] == '.')) ||
		(ARRAY_LAST(d))[0] == '.')
	{
		fta_popback(d, 1);
		ans--;
	}
}
