/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_match_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:41:46 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/21 11:51:24 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_re.h"
#include "libft.h"

char
	*ft_re_match_capture(const char *pattern, const char *group,
	const char *text)
{
	char *str;

	if (text == NULL)
		return (NULL);
	if (ft_re_match(pattern, text) == -1)
		return (NULL);
	str = ft_re_capture(group, text);
	return (str);
}

char
	*ft_re_capture(const char *group, const char *text)
{
	int		len;
	int		start;
	char	*str;
	char	*temp;

	if (text == NULL)
		return (NULL);
	start = ft_re_match(group, text);
	if (start == -1)
		return (NULL);
	text = text + start;
	len = ft_strlen(text);
	temp = ft_memalloc(ft_strlen(group) + 2);
	ft_memcpy(temp, group, ft_strlen(group));
	temp[ft_strlen(group)] = '$';
	temp[ft_strlen(group) + 1] = '\0';
	while (len > 0 && ft_re_matchn(temp, text, len) != 0)
		len--;
	free(temp);
	if (len == 0)
		return (NULL);
	str = ft_memalloc(len + 1);
	ft_memcpy(str, text, len);
	str[len] = '\0';
	return (str);
}

int
	ft_re_matchn(const char *pattern, const char *text, int len)
{
	char	*str;
	int		res;

	res = -1;
	str = ft_memalloc(len + 1);
	ft_memcpy(str, text, len);
	str[len] = '\0';
	res = ft_re_matchp(ft_re_compile(pattern), str);
	free(str);
	return (res);
}

int
	matchunused(t_regex p, t_regex *pattern, const char *text)
{
	if ((text[0] != '\0') && matchone(p, *text))
		matchpattern(pattern, text);
	return (1);
}
