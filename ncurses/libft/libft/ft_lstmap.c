/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 06:35:42 by jyeo              #+#    #+#             */
/*   Updated: 2017/11/15 23:28:45 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *begin;
	t_list *new;
	t_list *current;

	if (!lst || !f)
		return (NULL);
	begin = NULL;
	if ((new = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	while (lst)
	{
		new = (*f)(lst);
		if (!begin)
		{
			begin = new;
			current = begin;
		}
		else
		{
			current->next = new;
			current = current->next;
		}
		lst = lst->next;
	}
	return (begin);
}
