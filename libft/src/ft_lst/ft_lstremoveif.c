/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 14:45:50 by rnugroho          #+#    #+#             */
/*   Updated: 2017/11/19 14:45:50 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremoveif(t_list **begin_list, void *data_ref, int (*cmp)())
{
	if (!(*begin_list))
		return ;
	if ((*begin_list)->next)
		ft_lstremoveif(&((*begin_list)->next), data_ref, cmp);
	if (!((*cmp)((*begin_list)->content, data_ref)))
		*begin_list = (*begin_list)->next;
}
