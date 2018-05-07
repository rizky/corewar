/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 21:15:43 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/21 16:21:15 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WCHAR_H
# define FT_WCHAR_H

# include <wchar.h>
# include "libft.h"

size_t		ft_wstrlen(const wchar_t *wstr);
size_t		ft_wstrconv(char *buff, const wchar_t *wstr);
size_t		ft_wstrnconv(char *buff, const wchar_t *wstr, size_t n);
size_t		ft_widetoa(char *buff, wint_t w);

#endif
