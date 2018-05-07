/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddlast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 14:32:50 by rnugroho          #+#    #+#             */
/*   Updated: 2017/11/19 14:32:51 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddlast(t_list **alst, t_list *new)
{
	t_list	*list_ptr;

	list_ptr = *alst;
	if (list_ptr)
	{
		while (list_ptr->next)
			list_ptr = list_ptr->next;
		list_ptr->next = new;
	}
	else
		*alst = new;
}
