/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_helper_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:28:03 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/26 12:28:35 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vm.h"

void	*vm_memmark(void *dst, int i, size_t n)
{
	unsigned char *dst_p;

	dst_p = (unsigned char*)dst;
	while (n-- > 0)
		*dst_p++ = i;
	return (dst);
}
