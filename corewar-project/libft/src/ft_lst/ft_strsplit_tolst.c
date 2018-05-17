/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_tolst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 14:32:39 by rnugroho          #+#    #+#             */
/*   Updated: 2018/02/25 13:27:47 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_strsplit_tolst(char const *s, char c)
{
	char	**strtab;
	t_list	*lst;
	int		i;

	lst = NULL;
	strtab = ft_strsplit(s, c);
	i = 0;
	while (strtab[i])
	{
		ft_lstaddlast(&lst, ft_lstnew(strtab[i], ft_strlen(strtab[i])));
		i++;
	}
	return (lst);
}
