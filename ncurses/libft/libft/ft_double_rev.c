/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_rev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 06:50:37 by jyeo              #+#    #+#             */
/*   Updated: 2018/02/19 06:50:39 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_double_rev(void **ptr)
{
	int		start;
	int		end;
	void	*rev;

	rev = NULL;
	start = 0;
	end = ft_double_len(ptr) - 1;
	while (start < end)
	{
		rev = ptr[start];
		ptr[start] = ptr[end];
		ptr[end] = rev;
		end--;
		start++;
	}
}
