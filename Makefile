# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/01 20:07:00 by rnugroho          #+#    #+#              #
#    Updated: 2018/04/26 08:53:36 by fpetras          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= asm
FTASMPATH:= ft_asm/
FTASM:= ft_asm \
		asm_parser asm_parser_header \
		asm_parser_op asm_parser_param \
		asm_compiler asm_compiler_header \
		asm_print \
		asm_error \
		asm_free \
		asm_helper_1 asm_helper_2 asm_helper_3 asm_helper_4

NAME_VM:= corewar
FTVMPATH:= ft_vm/
FTVM:=	ft_vm \
		vm_decompiler \
		vm_decompiler_file \
		vm_executor \
		vm_checker \
		vm_op \
		vm_operations_1 vm_operations_2 vm_operations_3 vm_operations_4 \
		vm_op_print \
		vm_print \
		vm_error \
		vm_options \
		vm_helper_1

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
# CFLAGS:=-Wall -Wextra -Werror $(IFLAGS)
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

FILES_ASM:=$(addprefix $(FTASMPATH),$(FTASM))
FILES_VM:=$(addprefix $(FTVMPATH),$(FTVM))

# ------ Auto ------
SRC_ASM:=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILES_ASM)))
OBJ_ASM:=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES_ASM)))

SRC_VM:=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILES_VM)))
OBJ_VM:=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES_VM)))

# ==================
CCHF:=.cache_exists

all: $(NAME) $(NAME_VM)

$(NAME): $(OBJ_ASM)
	@$(MAKE) libft
	@echo $(CYAN) " - Compiling $@" $(RED)
	@$(COMPILER) $(CFLAGS) $(SRC_ASM) $(LFLAGS) -o $(NAME)
	@echo $(GREEN) " - OK" $(EOC)

$(NAME_VM): $(OBJ_VM)
	@$(MAKE) libft
	@echo $(CYAN) " - Compiling $@" $(RED)
	@$(COMPILER) $(CFLAGS) $(SRC_VM) $(LFLAGS) -o $(NAME_VM)
	@echo $(GREEN) " - OK" $(EOC)

$(CCHPATH)%.o: $(SRCPATH)%.c | $(CCHF)
	@echo $(PURPLE) " - Compiling $< into $@" $(EOC)
	@$(COMPILER) $(CFLAGS) -c $< -o $@

libft:
	@echo $(PURPLE) " - Compiling libft/src/* to libft/obj/*" $(PURPLE)
	@cd $(LFTDIR) && $(MAKE) -s

%.c:
	@echo $(RED)"Missing file : $@" $(EOC)

$(CCHF):
	@mkdir $(CCHPATH)
	@mkdir $(CCHPATH)$(FTASMPATH)
	@mkdir $(CCHPATH)$(FTVMPATH)
	@touch $(CCHF)

clean:
	@rm -rf $(CCHPATH)
	@rm -f $(CCHF)
	@cd $(LFTDIR) && $(MAKE) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_VM)
	@rm -rf $(NAME).dSYM/
	@rm -rf $(NAME_VM).dSYM/
	@cd $(LFTDIR) && $(MAKE) fclean
	@rm -f out1 out2
	@rm -f *.cor tests/asm/valid*/*.cor

re: fclean
	@$(MAKE) all

debug: $(OBJ_ASM)
	@echo $(CYAN) " - Compiling debug asm" $(EOC)
	@$(COMPILER) $(CFLAGS) $(SRC_ASM) $(LFLAGS) -g -o $(NAME)
	@echo $(CYAN) " - Compiling debug vm" $(EOC)
	@$(COMPILER) $(CFLAGS) $(SRC_VM) $(LFLAGS) -g -o $(NAME_VM)

norm:
	@norminette $(SRC_VM) $(HDRPATH) $(SRC_ASM) | grep -v	Norme -B1 || true
	@cd $(LFTDIR) && $(MAKE) norm

norm2:
	@sh ./norm/norm.sh

# ----- TEST UNIT ASM ------
T_ASM_DIR_ERROR = tests/asm/error/
T_ASM_FILES_ERROR:=$(shell cd $(T_ASM_DIR_ERROR); ls  | egrep '^$(T_FILE_ERROR).*.s$$' | sort -f )

test_asm_error : asm
	@if [[ $$(./asm -a $(T_ASM_DIR_ERROR)$(X) $(SILENT) ) < 0 ]] ; \
		then echo $(GREEN) " - [OK] $(T_ASM_DIR_ERROR)$(X)" $(EOC); \
		else echo $(RED) " - [KO] $(T_ASM_DIR_ERROR)$(X)" $(EOC) ; \
	fi

tests_asm_error: asm
	@echo $(CYAN) " - Test Error Cases" $(EOC)
	@$(foreach x, $(T_ASM_FILES_ERROR), $(MAKE) X=$x test_asm_error;)

T_ASM_DIR_VALID = tests/asm/valid/
T_ASM_DIR_VALID_2 = tests/asm/valid2/
T_ASM_FILES_VALID:=$(shell cd $(T_ASM_DIR_VALID); ls  | egrep '^.*.s$$' | sort -f )
T_ASM_FILES_BIN:=$(shell cd $(T_ASM_DIR_VALID); ls | egrep '^.*.s$$' | rev | cut -f 2- -d '.' | rev | sort -f )

test_asm_bin: asm
	@./asm $(T_ASM_DIR_VALID)$(X).s $(SILENT) ; true
	@./resources/binaries/asm $(T_ASM_DIR_VALID_2)$(X).s $(SILENT) ; true
	@if diff $(T_ASM_DIR_VALID)$(X).cor $(T_ASM_DIR_VALID_2)$(X).cor $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_ASM_DIR_VALID)$(X).cor" $(EOC); \
		else echo $(RED) " - [KO] $(T_ASM_DIR_VALID)$(X).cor" $(EOC) ; \
	fi

tests_asm_bin: asm
	@echo $(CYAN) " - Test Binary Files" $(EOC)
	@$(foreach x, $(T_ASM_FILES_BIN), $(MAKE) X=$x test_asm_bin;)

test_asm_valid : asm
	@./asm -a $(T_ASM_DIR_VALID)$(X) > out1 2>> out1; true
	@./resources/binaries/asm -a $(T_ASM_DIR_VALID)$(X) > out2; true
	@if diff out1 out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_ASM_DIR_VALID)$(X)" $(EOC); \
		else echo $(RED) " - [KO] $(T_ASM_DIR_VALID)$(X)" $(EOC) ; \
	fi

tests_asm_valid: asm
	@echo $(CYAN) " - Test Valid Cases" $(EOC)
	@$(foreach x, $(T_ASM_FILES_VALID), $(MAKE) X=$x test_asm_valid;)

tests_asm_v: asm tests_asm_valid tests_asm_error tests_asm_bin

tests_asm: asm
	@echo $(CYAN) " - Test Assembler" $(EOC)
	@$(MAKE) tests_asm_valid SILENT='> /dev/null'
	@$(MAKE) tests_asm_error SILENT='2> /dev/null'
	@$(MAKE) tests_asm_bin SILENT='> /dev/null'

test_asm_leak: asm
	@valgrind ./asm $(X) 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'

tests_asm_leak:
	@echo $(CYAN) " - Test Leaks" $(EOC)
	@$(foreach x, $(T_ASM_FILES_VALID), $(MAKE) X=$(T_ASM_DIR_VALID)$(x) test_asm_leak;)
	@$(foreach x, $(T_ASM_FILES_ERROR), $(MAKE) X=$(T_ASM_DIR_ERROR)$(x) test_asm_leak;)

tests_vm_error:
	@echo $(CYAN) " - Test Error Cases" $(EOC)
	./corewar -d 1 -n 0 tests/asm/valid/ex.cor -n 1 tests/asm/valid/Car.cor | head -4

tests_vm_valid:
	@echo $(CYAN) " - Test Valid Cases" $(EOC)
	./corewar -d 1 tests/asm/valid/ex.cor | head -4
	./corewar -d 1 -n 2 tests/asm/valid/ex.cor -n 1 tests/asm/valid/Car.cor | head -4
	./corewar -d 1 tests/asm/valid/ex.cor tests/asm/valid/Car.cor

tests_vm: corewar
	@echo $(CYAN) " - Test Virtual Machine" $(EOC)
	@$(MAKE) tests_vm_valid
	@$(MAKE) tests_vm_error

tests: tests_asm

.PHONY: all clean fclean re debug norm norm2 tests tests_asm test_asm_leak tests_asm_leak tests_asm_valid tests_asm_error tests_asm_v libft
