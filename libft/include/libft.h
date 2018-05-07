/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:38:44 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/13 10:34:38 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include "ft_array.h"
# include "ft_wchar.h"
# include "ft_date.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "ft_re.h"

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

t_list			*ft_create_elem(void *data);

int				ft_atoi(const char *str);
long			ft_atol(const char *str);
long long		ft_atoll(const char *str);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_ishexdigit(char c);
void			*ft_memccpy(void *dst,
				const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
int				is_in(char i, char const *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *s1);
size_t			ft_strlcat(char *dst,
				const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strnstr(const char *haystack,
				const char *needle, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
int				ft_tolower(int c);
int				ft_toupper(int c);

void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned intstart, size_t len);
char			*ft_strjoin(char const *s1, char const*s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
int				ft_wordcounter(const char *str, char c);
void			ft_strtab_free(char **strtab);
char			*ft_itoa(intmax_t n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

void			ft_lstaddlast(t_list **alst, t_list *new);
t_list			*ft_strsplit_tolst(char const *s, char c);
void			ft_lstclear(t_list **begin_list);
t_list			*ft_lstfind(t_list *begin_list, void *data_ref, int (*cmp)());
void			ft_lstremoveif(t_list **begin_list,
				void *data_ref, int (*cmp)());
void			ft_lstmerge(t_list **begin_list1, t_list *begin_list2);
t_list			*ft_lstlast(t_list *begin_list);
void			ft_lstrev(t_list **begin_list);
int				ft_lstsize(t_list *begin_list);
void			ft_lstswap(t_list **begin_list,
				t_list **current_list, t_list **prev_list);
void			ft_lstsort(t_list **begin_list, int (*cmp)());
void			ft_putlst(t_list *begin_lst);

long int		ft_round_base(double x, double f, int b);
double			ft_modf(double num);

/*
** Numbers manipulation tools
*/

# define ABS(V) ((V) < 0 ? -(V) : (V))
# define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
# define _MIN2(A,B) ((A) < (B) ? (A) : (B))

/*
** Numbers manipulation tools
*/

# define EOC 0
# define RED 1
# define GREEN 2
#endif
