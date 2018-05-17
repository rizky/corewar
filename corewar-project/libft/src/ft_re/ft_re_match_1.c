/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_match_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:22:38 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/21 11:39:15 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_re.h"

int
	matchdigit(char c)
{
	return ((c >= '0') && (c <= '9'));
}

int
	matchalpha(char c)
{
	return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}

int
	matchwhitespace(char c)
{
	return ((c == ' ') || (c == '\t') || (c == '\n')
			|| (c == '\r') || (c == '\f') || (c == '\v'));
}

int
	matchalphanum(char c)
{
	return ((c == '_') || matchalpha(c) || matchdigit(c));
}

int
	matchrange(char c, const char *str)
{
	return ((c != '-') && (str[0] != '\0') && (str[0] != '-') &&
		(str[1] == '-') && (str[1] != '\0') &&
		(str[2] != '\0') && ((c >= str[0]) && (c <= str[2])));
}
