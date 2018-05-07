/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fta_printdata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 04:19:28 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/16 15:39:38 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"
#include "libft.h"

void	fta_printdata_int(t_array *v)
{
	int i;

	i = 0;
	while (i < (int)v->size)
	{
		ft_printf("%d ", ((int*)v->data)[i]);
		i++;
	}
	ft_printf("\n");
}
