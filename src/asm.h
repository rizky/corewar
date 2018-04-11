/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:00:50 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/11 15:23:47 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/include/libft.h"
# include "../include/op.h"

# define NAME			1
# define NAME_LEN		2
# define COMMENT		3
# define COMMENT_LEN	4

typedef struct	s_asm
{
	int			i;
	char		*name;
	char		*comment;
	char		**file;
}				t_asm;

int				ft_parsing(t_asm *a);
int				ft_get_name(t_asm *a);
int				ft_get_comment(t_asm *a);

int				ft_error(int errcode, int status);

void			ft_handle_comments(char **file);
int				ft_line_is_empty(t_asm *a);
void			ft_skip_empty_lines(t_asm *a);
void			ft_trim_file(char **file);
void			ft_print_tab(char **tab);
int				ft_free_tab(char **tab, int status);

size_t			ft_strcspn(const char *s, const char *charset);

#endif
