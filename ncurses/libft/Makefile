# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyeo <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/11 14:15:58 by jyeo              #+#    #+#              #
#    Updated: 2018/01/25 00:00:51 by jyeo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAG = -Wall -Wextra -Werror

CC = gcc

LIBFT_DIR = 		./libft

LIBFT_SRC = 		libft/ft_atoi.c\
      				libft/ft_atoi_base.c\
      				libft/ft_isdigit.c\
      				libft/ft_lstdelone.c\
      				libft/ft_memccpy.c\
      				libft/ft_memmove.c\
      				libft/ft_putendl_fd.c\
      				libft/ft_strcat.c\
      				libft/ft_strdel.c\
      				libft/ft_strjoin.c\
      				libft/ft_strncat.c\
      				libft/ft_strnstr.c\
      				libft/ft_strtrim.c\
      				libft/ft_bzero.c\
      				libft/ft_isprint.c\
      				libft/ft_lstiter.c\
      				libft/ft_memchr.c\
      				libft/ft_memset.c\
      				libft/ft_putnbr.c\
      				libft/ft_strchr.c\
      				libft/ft_strdup.c\
      				libft/ft_strndup.c\
      				libft/ft_strlcat.c\
      				libft/ft_strncmp.c\
      				libft/ft_strrchr.c\
      				libft/ft_tolower.c\
      				libft/ft_isalnum.c\
      				libft/ft_itoa.c\
      				libft/ft_ltoa.c\
      				libft/ft_lltoa.c\
      				libft/ft_lltoa_base.c\
      				libft/ft_ltoa_base.c\
      				libft/ft_utoa.c\
      				libft/ft_ultoa.c\
      				libft/ft_ulltoa.c\
      				libft/ft_ultox.c\
      				libft/ft_itoa_base.c\
      				libft/ft_lstmap.c\
      				libft/ft_memcmp.c\
      				libft/ft_putchar.c\
      				libft/ft_putnbr_fd.c\
      				libft/ft_strclr.c\
      				libft/ft_strequ.c\
      				libft/ft_strlen.c\
      				libft/ft_strncpy.c\
      				libft/ft_strsplit.c\
      				libft/ft_toupper.c\
      				libft/ft_capitalize.c\
      				libft/ft_isalpha.c\
      				libft/ft_lstadd.c\
      				libft/ft_lstnew.c\
      				libft/ft_memcpy.c\
      				libft/ft_putchar_fd.c\
      				libft/ft_putstr.c\
      				libft/ft_strcmp.c\
      				libft/ft_striter.c\
      				libft/ft_strmap.c\
      				libft/ft_strnequ.c\
      				libft/ft_strstr.c\
      				libft/ft_isascii.c\
      				libft/ft_lstdel.c\
      				libft/ft_memalloc.c\
      				libft/ft_memdel.c\
      				libft/ft_putendl.c\
      				libft/ft_putstr_fd.c\
      				libft/ft_strcpy.c\
      				libft/ft_striteri.c\
      				libft/ft_strmapi.c\
      				libft/ft_strnew.c\
      				libft/ft_strsub.c\
      				libft/ft_puttab.c\
      				libft/ft_intlen.c\
      				libft/ft_intlen_base.c\
      				libft/ft_strrev.c\
      				libft/ft_imaxtoa_base.c\
      				libft/ft_free_double.c\
      				libft/ft_valid_int.c\
      				libft/ft_double_len.c\
      				libft/ft_double_rev.c\

GNL_SRC = 			get_next_line/get_next_line.c\

PRINTF_SRC = 		ft_printf/ft_flag.c\
      		 		ft_printf/ft_format.c\
      		 		ft_printf/ft_length.c\
      		 		ft_printf/ft_length_2.c\
      		 		ft_printf/ft_hash.c\
      		 		ft_printf/ft_printf.c\
      		 		ft_printf/ft_type.c\
      		 		ft_printf/ft_unicode.c\
      		 		ft_printf/ft_width.c\
      		 		ft_printf/ft_print_colourful.c\

INCLUDES = -I includes

LIBFT_OBJ = $(LIBFT_SRC:.c=.o)
GNL_OBJ = $(GNL_SRC:.c=.o)
PRINTF_OBJ = $(PRINTF_SRC:.c=.o)

ALL_OBJ = $(LIBFT_OBJ) $(GNL_OBJ) $(PRINTF_OBJ)

all: $(NAME)

$(NAME): $(ALL_OBJ)
	@ar rc $(NAME) $(ALL_OBJ)
	@ranlib $(NAME)

$(LIBFT_OBJ): %.o: %.c
	$(CC) $(FLAG) $(INCLUDES) -c $< -o $@

$(GNL_OBJ): %.o: %.c
	$(CC) $(FLAG) $(INCLUDES) -c $< -o $@

$(PRINTF_OBJ): %.o: %.c
	$(CC) $(FLAG) $(INCLUDES) -c $< -o $@

clean:
	@/bin/rm -f $(ALL_OBJ)

fclean:	clean
	@/bin/rm -f $(NAME)

re:	fclean all
