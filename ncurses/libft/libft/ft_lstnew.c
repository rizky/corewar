/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 05:01:42 by jyeo              #+#    #+#             */
/*   Updated: 2017/11/14 08:56:58 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if ((list = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (list)
	{
		if (content == NULL)
		{
			list->content = (void *)content;
			list->content_size = 0;
		}
		else
		{
			list->content = ft_strdup(content);
			list->content_size = content_size;
		}
		list->next = NULL;
	}
	return (list);
}
