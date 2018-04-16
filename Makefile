# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/01 20:07:00 by rnugroho          #+#    #+#              #
#    Updated: 2018/04/16 09:31:08 by rnugroho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= asm
NAME_CW:= corewar
FILE_A:= ft_asm
FILE_CW:= ft_corewar 
FILES:= asm_parser asm_parser_header \
		asm_parser_op asm_parser_param \
		asm_compiler asm_compiler_header \
		asm_checker_op asm_checker_labels \
		asm_error \
		asm_helper_1 asm_helper_2 \
		asm_print \
		ft_strcspn \
		ft_strcdup

# ----- Libft ------
LFTDIR:=./libft
# ==================

# ------------------
COMPILER:=clang
LINKER:=ar rc
SRCPATH:=src/
HDRPATH:=include/
CCHPATH:=obj/
IFLAGS:=-I $(HDRPATH) -I $(LFTDIR)/include
LFLAGS:=-L $(LFTDIR) -lft
CFLAGS:=-Wall -Wextra $(IFLAGS)
# ==================

# ----- Colors -----
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
CYAN:="\033[1;35m"
PURPLE:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"
# ==================

# ------ Auto ------
SRC:=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILES)))
SRC_CW:=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILE_CW)))
SRC_A:=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILE_A)))
OBJ:=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES)))
OBJ_A:=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILE_A)))
OBJ_CW:=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILE_CW)))
# ==================
CCHF:=.cache_exists

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_A)
	@cd $(LFTDIR) && $(MAKE)
	@echo $(CYAN) " - Compiling $@" $(RED)
	@$(COMPILER) $(CFLAGS) $(SRC) $(LFLAGS) $(SRCPATH)$(FILE_A).c -o $(NAME)
	@echo $(GREEN) " - OK" $(EOC)

$(NAME_CW): $(OBJ) $(OBJ_CW)
	@cd $(LFTDIR) && $(MAKE)
	@echo $(CYAN) " - Compiling $@" $(RED)
	@$(COMPILER) $(CFLAGS) $(SRC) $(LFLAGS) $(SRC_CW) -o $(NAME_CW)
	@echo $(GREEN) " - OK" $(EOC)

$(CCHPATH)%.o: $(SRCPATH)%.c | $(CCHF)
	@echo $(PURPLE) " - Compiling $< into $@" $(EOC)
	@$(COMPILER) $(CFLAGS) -c $< -o $@

%.c:
	@echo $(RED)"Missing file : $@" $(EOC)

$(CCHF):
	@mkdir $(CCHPATH)
	@touch $(CCHF)

clean:
	@rm -rf $(CCHPATH)
	@rm -f $(CCHF)
	@cd $(LFTDIR) && $(MAKE) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_CW)
	@rm -rf $(NAME).dSYM/
	@rm -rf $(NAME_CW).dSYM/
	@cd $(LFTDIR) && $(MAKE) fclean

re: fclean
	@$(MAKE) all

debug: $(NAME)
	@$(COMPILER) $(CFLAGS) $(SRC) $(LFLAGS) -g $(SRCPATH)$(FILE_A).c -o $(NAME)

norm:
	@norminette $(SRC) $(HDRPATH) | grep -v	Norme -B1 || true
	@cd $(LFTDIR) && $(MAKE) norm

norm2:
	@sh ./norm/norm.sh

.PHONY: all clean fclean re test norme test_ch test_pw debug check
