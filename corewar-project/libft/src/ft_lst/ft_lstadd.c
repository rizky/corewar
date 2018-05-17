/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 21:07:38 by rnugroho          #+#    #+#             */
/*   Updated: 2017/11/15 21:07:39 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*list_ptr;

	if (*alst)
	{
		list_ptr = new;
		if (list_ptr)
		{
			list_ptr->next = (*alst);
			(*alst) = list_ptr;
		}
	}
	else
		*alst = new;
}
