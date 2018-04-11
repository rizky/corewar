/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:00:50 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/11 09:54:30 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/include/libft.h"
# include "../include/op.h"

typedef struct	s_asm
{
	int			i;
	char		*name;
	char		*comment;
	char		**file;
}				t_asm;

int				ft_parsing(t_asm *a);

void			ft_handle_comments(char **file);
int				ft_line_is_empty(t_asm *a);
void			ft_skip_empty_lines(t_asm *a);
void			ft_print_tab(char **tab);
void			ft_free_tab(char **tab);

//char			*ft_strcdup(const char *s1, char c);

#endif
