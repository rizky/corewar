/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:36:26 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/14 00:38:49 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define FTPF_CV "sSpdDioOuUxXcCbn"
# define FTPF_NUMERIC "diouDOUxXpb"
# define FTPF_LM "hljztL"
# define FTPF_SWITCHES "0+- #_"
# define NEW_MODIFIER (t_modifier){{{0, 0, 0, 0, 0, 0}}, 0, 0, 0, 0, 0, 0, -1};

typedef struct		s_modifier
{
	union
	{
		char		t[6];
		struct
		{
			char	zero;
			char	plus;
			char	minus;
			char	space;
			char	alternate;
			char	underscore;
		}			n;
	}				booleans;
	char			conversion;
	char			length;
	int				size;
	int				quote;
	int				ndollar;
	int				mindex;
	int				precision;
}					t_modifier;

int					ft_printf(char const *format, ...);
int					ft_printfln(char const *format, ...);
int					ft_dprintf(int fd, char const *format, ...);
int					ft_asprintf(char **ret, char const *format, ...);
char				*ft_rasprintf(int *ans, char const *format, ...);
int					ft_dollarprintf(char const *format, ...);

int					ft_vprintf(char const *format, va_list ap);
int					ft_vdprintf(int fd, char const *format, va_list ap);
int					ft_vasprintf(char **ret, char const *s, va_list ap);

int					pf_convert(t_modifier *m, t_array *d,
					va_list ap, va_list dap);
char				*pf_next_specifier(char const *s, t_array *d);
int					pf_unsigned_integer(t_modifier *m,
					t_array *d, va_list ap, int b);
int					pf_signed_integer(t_modifier *m,
					t_array *d, va_list ap, int b);

int					pf_itoa_base(t_array *d, intmax_t n, int b, char info);
int					pf_rtoa(t_array *d, long double x, int b, t_modifier *m);
int					pf_signed_double_e(t_modifier *m,
					t_array *d, long double arg, char *c);
int					pf_signed_double_g(t_modifier *m,
					t_array *d, long double arg, char *c);
int					pf_signed_double_a(t_modifier *m,
					t_array *d, long double arg, char *c);

int					pf_cv_s(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_ws(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_p(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_di(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_u(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_x(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_cx(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_o(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_c(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_wc(t_modifier *m, t_array *d, va_list ap);

int					pf_cv_b(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_n(t_modifier *m, t_array *d, va_list ap);

int					pf_cv_f(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_cf(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_e(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_ce(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_g(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_cg(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_a(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_ca(t_modifier *m, t_array *d, va_list ap);

int					pf_cv_w(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_cw(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_ct(t_modifier *m, t_array *d, va_list ap);

int					pf_cv_y(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_r(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_q(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_m(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_cq(t_modifier *m, t_array *d, va_list ap);
int					pf_cv_v(t_modifier *m, t_array *d, va_list ap);
int					pf_culturization(t_array *d, char c);
#endif
