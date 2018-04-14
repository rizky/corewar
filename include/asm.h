/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:00:50 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/14 14:58:52 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

# define SOURCEFILE		1
# define EMPTY			2
# define NEWLINE		3
# define MALLOC			4
# define NAME			5
# define NAME_LEN		6
# define COMMENT		7
# define COMMENT_LEN	8
# define OP				9

# define PTYPE_REG 0
# define PTYPE_IND 1
# define PTYPE_DIR 2

typedef struct	s_param
{
	char		*str;
	int			type;
	int			size;
	int			value;
}				t_param;

typedef struct	s_op
{
	int			opcode;
	int			size;
	t_param		params[3];
	int			param_counter;
	int			offset;
}				t_op;

typedef struct	s_asm
{
	int			i;
	char		*name;
	char		*comment;
	char		**file;
	t_op		ops[1000];
	int			op_counter;
}				t_asm;

int				ft_parsing(t_asm *a, header_t *h);
int				ft_get_name(t_asm *a, header_t *h);
int				ft_get_comment(t_asm *a, header_t *h);
int				ft_get_op(t_asm *a, header_t *h);
int				ft_error(int errcode, int status);

int				ft_file_is_empty(char *file);
int				ft_line_is_empty(t_asm *a);
void			ft_skip_empty_lines(t_asm *a);
void			ft_handle_comments(char **file);
void			ft_trim_file(char **file);
void			ft_print_tab(char **tab);
int				ft_free(char *str, int status);
int				ft_free_tab(char **tab, int status);

#endif
