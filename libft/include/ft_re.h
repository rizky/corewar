/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:24:05 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/21 12:18:32 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RE_H
# define FT_RE_H

# define MAX_REGEXP_OBJECTS 30
# define MAX_CHAR_CLASS_LEN 40

enum
{
	UNUSED,
	DOT,
	BEGIN,
	END,
	QUESTIONMARK,
	STAR,
	PLUS,
	CHAR,
	CHAR_CLASS,
	INV_CHAR_CLASS,
	DIGIT,
	NOT_DIGIT,
	ALPHA,
	NOT_ALPHA,
	WHITESPACE,
	NOT_WHITESPACE
};

typedef struct			s_regex
{
	unsigned char		type;
	union
	{
		unsigned char	ch;
		unsigned char	*ccl;
	}					t_char;
}						t_regex;

typedef struct s_regex*	t_re;

t_re					ft_re_compile(const char *pattern);
int						ft_re_matchp(t_re pattern, const char *text);
int						ft_re_match(const char *pattern, const char *text);
int						matchpattern(t_regex *pattern, const char *text);
int						matchcharclass(char c, const char *str);
int						matchstar(t_regex p, t_regex *pattern,
						const char *text);
int						matchplus(t_regex p, t_regex *pattern,
						const char *text);
int						matchone(t_regex p, char c);
int						matchdigit(char c);
int						matchalpha(char c);
int						matchalphanum(char c);
int						matchwhitespace(char c);
int						matchmetachar(char c, const char *str);
int						matchrange(char c, const char *str);
int						ismetachar(char c);
int						ft_re_matchn(const char *pattern, const char *text,
						int len);
char					*ft_re_match_capture(const char *pattern,
						const char *group, const char *text);
char					*ft_re_capture(const char *group, const char *text);
int						matchunused(t_regex p, t_regex *pattern,
						const char *text);

#endif
