/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 06:16:44 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/10 06:16:47 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *str)
{
	int		start;
	int		end;
	char	rev;

	start = 0;
	end = (ft_strlen(str) - 1);
	while (start < end)
	{
		rev = str[start];
		str[start] = str[end];
		str[end] = rev;
		end--;
		start++;
	}
}
