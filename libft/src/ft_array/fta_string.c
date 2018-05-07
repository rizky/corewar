/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fta_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 18:09:32 by rnugroho          #+#    #+#             */
/*   Updated: 2018/02/17 11:23:04 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"
#include "libft.h"

#define TMP_STRING_APPEND(A,S) fta_append(A, S, ft_strlen(S))

/*
** Array::string
** -
** toString
** description
** -
** _f_ converts an element to a string.
** -
** Returns a string representing the given array.
*/

char	*fta_string(t_array *self, char *(*f)(void *))
{
	t_array		ans[1];
	void		*iterator;
	char		*tmp;

	*ans = NEW_ARRAY(char);
	fta_reserve(self, self->size * 3 + 10);
	TMP_STRING_APPEND(ans, "[|");
	iterator = ARRAY_START(self);
	tmp = f(iterator);
	TMP_STRING_APPEND(ans, tmp);
	while (ARRAY_HASNEXT(self, iterator))
	{
		TMP_STRING_APPEND(ans, ", ");
		tmp = f(iterator);
		TMP_STRING_APPEND(ans, tmp);
	}
	fta_append(ans, "|]", 3);
	return ((char *)ans->data);
}

#undef TMP_STRING_APPEND
