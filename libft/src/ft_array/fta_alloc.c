/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fta_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 17:21:32 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/23 11:44:05 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_array.h"
#include "libft.h"

/*
** Array::alloc
** -
** Allocates an array and its data.
** -
** _type_size_ should equal to the returned value of sizeof(T)
** -
** Returns the allocated array,
** or NULL if malloc failed.
*/

t_array		*fta_alloc(size_t type_size)
{
	t_array	*ans;

	if (!(ans = (t_array *)malloc(sizeof(t_array))))
		return (NULL);
	ft_bzero(ans, sizeof(t_array));
	ans->type_size = type_size;
	return (fta_reserve(ans, 1) ? NULL : ans);
}
