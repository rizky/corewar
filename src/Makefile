# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpetras <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/10 13:57:29 by fpetras           #+#    #+#              #
#    Updated: 2018/04/11 14:58:05 by fpetras          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRC = asm.c \
	  parsing.c \
	  header.c \
	  error.c \
	  utilities.c \
	  utilities_2.c \
	  ft_strcspn.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ../libft
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) ../libft/libft.a

clean:
	@make clean -C ../libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C ../libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
