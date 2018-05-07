/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 14:48:04 by rnugroho          #+#    #+#             */
/*   Updated: 2017/11/19 14:48:04 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **begin_list, int (*cmp)())
{
	t_list	*current_list;
	t_list	*prev_list;

	current_list = *begin_list;
	if (!current_list)
		return ;
	while (current_list->next)
	{
		if (cmp(current_list->content, current_list->next->content) > 0)
		{
			ft_lstswap(begin_list, &current_list, &prev_list);
		}
		else
		{
			prev_list = current_list;
			current_list = current_list->next;
		}
	}
}
