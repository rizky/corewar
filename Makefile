# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/01 20:07:00 by rnugroho          #+#    #+#              #
#    Updated: 2018/04/18 11:05:55 by rnugroho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= asm
FILE:= ft_asm
FILES:= asm_parser asm_parser_header \
		asm_parser_op asm_parser_param \
		asm_compiler asm_compiler_header \
		asm_print \
		asm_error \
		asm_helper_1 asm_helper_2 asm_helper_3 asm_helper_4

# FTREPATH:= libft/src/ft_re/
# FTRE:= ft_re ft_re_match_1 ft_re_match_2 ft_re_match_3 ft_re_match_4

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
OBJ:=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES)))

# SRC_RE+=$(addprefix $(FTREPATH),$(addsuffix .c,$(FTRE)))
# ==================
CCHF:=.cache_exists

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(PURPLE) " - Compiling libft/src/* to libft/obj/*" $(PURPLE)
	@cd $(LFTDIR) && $(MAKE)
	@echo $(CYAN) " - Compiling $@" $(RED)
	@$(COMPILER) $(CFLAGS) $(SRC) $(LFLAGS) $(SRCPATH)$(FILE).c -o $(NAME)
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
	@rm -rf $(NAME).dSYM/
	@cd $(LFTDIR) && $(MAKE) fclean

re: fclean
	@$(MAKE) all

debug: $(NAME)
	@echo $(CYAN) " - Compiling debug asm" $(EOC)
	@$(COMPILER) $(CFLAGS) $(SRC) $(LFLAGS) -g $(SRCPATH)$(FILE).c -o $(NAME)

norm:
	@norminette $(SRC) $(HDRPATH) | grep -v	Norme -B1 || true
	@cd $(LFTDIR) && $(MAKE) norm

norm2:
	@sh ./norm/norm.sh

test_leaks:
	@valgrind ./asm -a resources/champs/ex.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/champs/42.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/bee_gees.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/bigzork.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/fluttershy.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/helltrain.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/jumper.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/bigzork.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/maxidef.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/slider2.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/turtle.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/aff_no_OCP.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/flipped_name_comment.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/empty_namecomment.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/end_comment.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/valid/nl_at_header.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'
	@valgrind ./asm -a resources/errors/nl_at_header_error.s 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'

# ----- TEST UNIT ------
T_DIR_ERROR = tests/error/
T_FILES_ERROR:=$(shell cd $(T_DIR_ERROR); ls  | egrep '^.*.s$$' | sort -n )

test_error :
	@if [[ $$(./asm -a $(T_DIR_ERROR)$(X) 2> /dev/null)  < 0 ]] ; \
		then echo $(GREEN) " - [OK] $(T_DIR_ERROR)$(X)" $(EOC); \
		else echo $(RED) " - [KO] $(T_DIR_ERROR)$(X)" $(EOC) ; \
	fi

tests_error: all
	@echo $(CYAN) " - Test Error Cases" $(EOC)
	@$(foreach x, $(T_FILES_ERROR), $(MAKE) X=$x test_error;)

T_DIR_VALID = tests/valid/
T_FILES_VALID:=$(shell cd $(T_DIR_VALID); ls  | egrep '^.*.s$$' | sort -n )

test_valid :
	@if [[ $$(./asm -a $(T_DIR_VALID)$(X) > out1 && ./resources/vm_champs/asm -a $(T_DIR_VALID)$(X) > out2 && diff out1 out2) != 0 ]] ; \
		then echo $(GREEN) " - [OK] $(T_DIR_VALID)$(X)" $(EOC); \
		else echo $(RED) " - [KO] $(T_DIR_VALID)$(X)" $(EOC) ; \
	fi

tests_valid: all
	@echo $(CYAN) " - Test Valid Cases" $(EOC)
	@$(foreach x, $(T_FILES_VALID), $(MAKE) X=$x test_valid;)

test: tests_valid tests_error
	
.PHONY: all clean fclean re debug norm norm2 test test_leaks
