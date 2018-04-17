# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/01 20:07:00 by rnugroho          #+#    #+#              #
#    Updated: 2018/04/17 23:12:28 by rnugroho         ###   ########.fr        #
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
		asm_helper_1 asm_helper_2 asm_helper_3 \
		asm_helper_4 \
		asm_print \

FTREPATH:= libft/src/ft_re/
FTRE:= ft_re ft_re_match_1 ft_re_match_2 ft_re_match_3 ft_re_match_4

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

SRC_RE+=$(addprefix $(FTREPATH),$(addsuffix .c,$(FTRE)))
# ==================
CCHF:=.cache_exists

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_A)
	@cd $(LFTDIR) && $(MAKE)
	@echo $(CYAN) " - Compiling $@" $(RED)
	@$(COMPILER) $(CFLAGS) $(SRC) $(SRC_RE) $(LFLAGS) $(SRCPATH)$(FILE_A).c -o $(NAME)
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
	@$(COMPILER) $(CFLAGS) $(SRC) $(SRC_RE) $(LFLAGS) -g $(SRCPATH)$(FILE_A).c -o $(NAME)

norm:
	@norminette $(SRC) $(HDRPATH) | grep -v	Norme -B1 || true
	@cd $(LFTDIR) && $(MAKE) norm

norm2:
	@sh ./norm/norm.sh

test: $(NAME)
	@echo $(GREEN) "Test Cases" $(EOC)
	@./asm -a resources/champs/ex.s > out1 && ./resources/vm_champs/asm -a resources/champs/ex.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/champs/42.s > out1 && ./resources/vm_champs/asm -a resources/champs/42.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/bee_gees.s > out1 && ./resources/vm_champs/asm -a resources/valid/bee_gees.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/bigzork.s > out1 && ./resources/vm_champs/asm -a resources/valid/bigzork.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/fluttershy.s > out1 && ./resources/vm_champs/asm -a resources/valid/fluttershy.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/helltrain.s > out1 && ./resources/vm_champs/asm -a resources/valid/helltrain.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/jumper.s > out1 && ./resources/vm_champs/asm -a resources/valid/jumper.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/bigzork.s > out1 && ./resources/vm_champs/asm -a resources/valid/bigzork.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/maxidef.s > out1 && ./resources/vm_champs/asm -a resources/valid/maxidef.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/slider2.s > out1 && ./resources/vm_champs/asm -a resources/valid/slider2.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/turtle.s > out1 && ./resources/vm_champs/asm -a resources/valid/turtle.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/aff_no_OCP.s > out1 && ./resources/vm_champs/asm -a resources/valid/aff_no_OCP.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/flipped_name_comment.s > out1 && ./resources/vm_champs/asm -a resources/valid/flipped_name_comment.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/empty_namecomment.s > out1 && ./resources/vm_champs/asm -a resources/valid/empty_namecomment.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/end_comment.s > out1 && ./resources/vm_champs/asm -a resources/valid/end_comment.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/hash_at_header.s > out1 && ./resources/vm_champs/asm -a resources/valid/hash_at_header.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/no_space_between_op_and_param.s > out1 && ./resources/vm_champs/asm -a resources/valid/no_space_between_op_and_param.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/sq_at_header.s > out1 && ./resources/vm_champs/asm -a resources/valid/sq_at_header.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	@./asm -a resources/valid/nl_at_header.s > out1 && ./resources/vm_champs/asm -a resources/valid/nl_at_header.s > out2 && diff out1 out2 && echo $(GREEN) " - OK" $(EOC) ; true
	
	@if [[ $$(./asm -a resources/errors/bad_param_type.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	@if [[ $$(./asm -a resources/errors/double_commas.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	@if [[ $$(./asm -a resources/errors/extra.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	@if [[ $$(./asm -a resources/errors/extra2.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	@if [[ $$(./asm -a resources/errors/no_code.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	@if [[ $$(./asm -a resources/errors/plus_minus.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	@if [[ $$(./asm -a resources/errors/r100.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	@if [[ $$(./asm -a resources/errors/comma_at_end_of_last_param.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	@if [[ $$(./asm -a resources/errors/double_operation_on_single_line.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	@if [[ $$(./asm -a resources/errors/REG100.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	@if [[ $$(./asm -a resources/errors/double_comments.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	@if [[ $$(./asm -a resources/errors/double_names.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	@if [[ $$(./asm -a resources/errors/null_name.s 2> /dev/null)  < 0 ]] ; then echo $(GREEN) " - OK" $(EOC); else echo KO ; fi
	
	

test_leak:
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
	

.PHONY: all clean fclean re test norme test_ch test_pw debug check
