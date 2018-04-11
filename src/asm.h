/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:00:50 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/11 09:27:37 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/include/libft.h"
# include "../include/op.h"

typedef struct	s_asm
{
	int			l; //lines
	int			c; //columns
	char		*name;
	char		*comment;
	char		**file;
}				t_asm;

void			ft_handle_comments(char **file);
void			ft_print_tab(char **tab);
void			ft_free_tab(char **tab);

#endif
