/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 11:37:16 by jyeo              #+#    #+#             */
/*   Updated: 2017/12/17 19:36:34 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <fcntl.h>
# include <stdarg.h>
# define FREE(pointer)({free(pointer);pointer=NULL;})
# define JOIN(tmp,ar,s1,s2)({tmp=ar;ar=ft_strjoin(s1,s2);free(tmp);tmp=NULL;})
# define STRDUP(tmp,s1,s2)({tmp=s1;s1=ft_strdup(s2);free(tmp);tmp=NULL;})
# define ERROR(cond,val)({if((cond))return(val);})
# define FERROR(cond,arr,val)({if((cond)){free(arr);arr=NULL;return(val);}})

typedef	struct	s_width
{
	int			precision;
	int			align;
	int			width;
}				t_width;

typedef	struct	s_flag
{
	char		*pad;
	char		*f;
}				t_flag;

int				ft_printf(const char *str, ...);
int				ft_move_point(char **pointer, int index);
int				ft_type(const char **str, char **s, va_list ap);
int				ft_format(const char **str, char **buf, va_list ap);
char			*ft_unicode(int unicode);
int				ft_width(const char **str, t_width *width, t_flag *flag, int i);
int				ft_get_pres(const char **str);
int				ft_precision(const char **str, char **s, t_flag *f, t_width *w);
int				ft_length(const char **str, char **s, va_list ap, int i);
int				ft_type_wchar(char **s, va_list ap, char type, int p);
int				ft_flag0(char **buf, char **s, t_flag flag);
int				ft_flag_p(const char **s, t_flag *flag, t_width *w, va_list ap);
int				ft_align(char **buf, char **s, char *padding, t_width width);
int				ft_flag_hash(const char **str, char **f, char **s, t_width *w);
int				ft_length_ll(const char **str, char **s, va_list ap);
int				ft_length_hh(const char **str, char **s, va_list ap);
int				ft_length_l(const char **str, char **s, va_list ap);
int				ft_print_colourful(wchar_t *str, int colour);

#endif
