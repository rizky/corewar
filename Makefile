# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/01 20:07:00 by rnugroho          #+#    #+#              #
#    Updated: 2018/05/05 17:12:11 by rnugroho         ###   ########.fr        #
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
		vm_options \
		vm_decompiler \
		vm_decompiler_file \
		vm_checker \
		vm_executor \
		vm_print \
		vm_error \
		vm_free \
		vm_helper_1 vm_helper_2

FTVMDRAWPATH:= ft_vm/vm_draw/
FTVMDRAW:= draw_animation_1 \
		draw_animation_2 \
		draw_end \
		draw_game \
		draw_info \
		draw_player_info \
		draw_init \
		draw_key_utils \
		draw_nyan \
		draw

FTVMOPPATH:= ft_vm/vm_op/
FTVMOP:= op_and op_add op_aff op_fork \
		op_ld op_ldi op_lfork op_live \
		op_lld op_lldi op_or op_st \
		op_sti op_sub op_xor op_zjmp

# ----- Libft ------
LFTDIR:=./libft
# ==================

# ------------------
COMPILER:=gcc
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

FILES_ASM:=$(addprefix $(FTASMPATH),$(FTASM))
FILES_VM:=$(addprefix $(FTVMPATH),$(FTVM))
FILES_VM_DRAW:=$(addprefix $(FTVMDRAWPATH),$(FTVMDRAW))
FILES_VM_OP:=$(addprefix $(FTVMOPPATH),$(FTVMOP))

# ------ Auto ------
SRC_ASM:=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILES_ASM)))
OBJ_ASM:=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES_ASM)))

SRC_VM:=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILES_VM)))
OBJ_VM:=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES_VM)))

SRC_VM+=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILES_VM_DRAW)))
OBJ_VM+=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES_VM_DRAW)))

SRC_VM+=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILES_VM_OP)))
OBJ_VM+=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES_VM_OP)))

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
	@$(COMPILER) $(CFLAGS) $(SRC_VM) $(LFLAGS) -o $(NAME_VM) -lncurses
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
	@mkdir $(CCHPATH)$(FTVMDRAWPATH)
	@mkdir $(CCHPATH)$(FTVMOPPATH)
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

re: fclean
	@$(MAKE) all

assemble: asm
	@./asm -m tests/asm/v*/*.s tests/vm/[bco]*/*.s

clean_cor:
	@rm -f tests/asm/v*/*.cor tests/vm/[bco]*/*.cor

debug: $(OBJ_ASM) $(OBJ_VM)
	@echo $(CYAN) " - Compiling debug asm" $(EOC)
	@$(COMPILER) $(CFLAGS) $(SRC_ASM) $(LFLAGS) -g -o $(NAME)
	@echo $(CYAN) " - Compiling debug vm" $(EOC)
	@$(COMPILER) $(CFLAGS) $(SRC_VM) $(LFLAGS) -g -o $(NAME_VM) -lncurses

norm: all
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

# ----- TEST UNIT VM ------
T_VM_DIR_OP = tests/vm/op/
T_VM_FILES_OP:=$(shell cd $(T_VM_DIR_OP); ls | egrep '^$(T_FILE).*.s$$' | rev | cut -f 2- -d '.' | rev | sort -f )
T_VM_DIR_C = tests/vm/champ/
T_VM_FILES_C:=$(shell cd $(T_VM_DIR_C); ls | egrep '^$(T_FILE).*.s$$' | rev | cut -f 2- -d '.' | rev | sort -f )
T_VM_DIR_OCP = tests/vm/ocp/
T_VM_FILES_OCP:=$(shell cd $(T_VM_DIR_OCP); ls | egrep '^$(T_FILE).*.s$$' | rev | cut -f 2- -d '.' | rev | sort -f )
DUMP = 150

OK = 0
TOTAL = 0
test_vm_op : corewar
	@./resources/binaries/asm $(T_VM_DIR)$(X).s > /dev/null; true
	@./corewar -v 30 $(T_VM_DIR)$(X).cor > out1 2>> out1; true
	@./resources/binaries/corewar -v 30 -a $(T_VM_DIR)$(X).cor > out2; true
	@if diff out1 out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_VM_DIR)$(X)" $(EOC) ; \
		else echo $(RED) " - [KO] $(T_VM_DIR)$(X)" $(EOC) ; \
	fi

tests_vm_op: corewar
	@echo $(CYAN) " - Test Basic Operations" $(EOC)
	@$(foreach x, $(T_VM_FILES_OP), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_OP) test_vm_op;)

tests_vm_dump_champs: corewar
	@echo $(CYAN) " - Test Memory Dump on Champs $(DUMP)" $(EOC)
	@$(foreach x, $(T_VM_FILES_C), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_C) test_vm_dump;)

NUMBERS = 1 20 50 80 150 200 600 800 1400 2400 5000 8000 10000 50000
tests_vm_dump_champs_loop: corewar
	@$(foreach x, $(NUMBERS), $(MAKE) DUMP=$x T_VM_DIR=$(T_VM_DIR_C) tests_vm_dump_champs;)

test_vm_op_champ : corewar
	@./resources/binaries/asm $(T_VM_DIR)$(X).s > /dev/null; true
	@./corewar -v 30 $(T_VM_DIR)$(X).cor > $(T_VM_DIR)$(X).out1 2>> $(T_VM_DIR)$(X).out1; true
	@./resources/binaries/corewar -v 30 -a $(T_VM_DIR)$(X).cor > $(T_VM_DIR)$(X).out2; true
	@if diff $(T_VM_DIR)$(X).out1 $(T_VM_DIR)$(X).out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_VM_DIR)$(X)" $(EOC) && rm $(T_VM_DIR)$(X).out1 $(T_VM_DIR)$(X).out2; \
		else echo $(RED) " - [KO] $(T_VM_DIR)$(X)" $(EOC) ; \
	fi

tests_vm_op_champs: corewar
	@echo $(CYAN) " - Test Basic Operations on Champs" $(EOC)
	@$(foreach x, $(T_VM_FILES_C), ($(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_C) SILENT='> /dev/null' test_vm_op_champ;)&)

tests_vm_ocp: corewar
	@echo $(CYAN) " - Test Basic Operations on Champs" $(EOC)
	@$(foreach x, $(T_VM_FILES_OCP), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_OCP) test_vm_op;)

test_vm_dump : corewar
	@./resources/binaries/asm $(T_VM_DIR)$(X).s > /dev/null; true
	@./corewar -dump $(DUMP) $(T_VM_DIR)$(X).cor > out1 2>> out1; true
	@./resources/binaries/corewar -d $(DUMP) $(T_VM_DIR)$(X).cor > out2; true
	@if diff out1 out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_VM_DIR)$(X)" $(EOC); \
		else echo $(RED) " - [KO] $(T_VM_DIR)$(X)" $(EOC) ; \
	fi

tests_vm_dump: corewar
	@echo $(CYAN) " - Test Memory Dump $(DUMP)" $(EOC)
	@$(foreach x, $(T_VM_FILES_OP), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_OP) test_vm_dump;)
	@$(foreach x, $(T_VM_FILES_HC), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_HC) test_vm_dump;)

NUMBERS = 1 20 50 80 150 200 600 800 1400 2400 5000 8000 10000 20000
tests_vm_dump_loop: corewar
	@$(foreach x, $(NUMBERS), $(MAKE) DUMP=$x T_VM_DIR=$(T_VM_DIR_OP) tests_vm_dump;)

test_vm_leak: corewar
	@valgrind ./corewar $(X) 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*'

tests_vm_leak:
	@echo $(CYAN) " - Test Leaks" $(EOC)
	@$(foreach x, $(T_VM_FILES_OP), $(MAKE) X=$(T_VM_DIR_OP)$(x) test_vm_leak;)

T_VM_DIR_B = tests/vm/battle/
T_VM_FILES_B:=$(shell cd $(T_VM_DIR_B); ls | egrep '^$(T_FILE).*.s$$' | egrep '^[^X]+.s$$' | rev | cut -f 2- -d '.' | rev | sort -f )

test_vm_battle : corewar
	@./resources/binaries/asm $(T_VM_DIR_B)$(X).s > /dev/null; true
	@./resources/binaries/asm $(T_VM_DIR_B)$(X)X.s > /dev/null; true
	@./corewar -v30 $(T_VM_DIR_B)$(X).cor $(T_VM_DIR_B)$(X)X.cor > out1 2>> out1; true
	@./resources/binaries/corewar -v 30 -a $(T_VM_DIR_B)$(X).cor $(T_VM_DIR_B)$(X)X.cor > out2; true
	@if diff out1 out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_VM_DIR_B)$(X)" $(EOC); \
		else echo $(RED) " - [KO] $(T_VM_DIR_B)$(X)" $(EOC) ; \
	fi

tests_vm_battle: corewar
	@echo $(CYAN) " - Test Battle" $(EOC)
	@$(foreach x, $(T_VM_FILES_B), $(MAKE) X=$x test_vm_battle;)

T_VM_DIR_O = tests/vm/overflow/
T_VM_FILES_O:=$(shell cd $(T_VM_DIR_O); ls | egrep '^$(T_FILE).*.s$$' | rev | cut -f 2- -d '.' | rev | sort -f )

.PHONY: test_vm_op_overflow test_vm_dump_overflow tests_vm_overflow

test_vm_dump_overflow : corewar
	@./resources/binaries/asm $(T_VM_DIR)$(X).s > /dev/null; true
	@./corewar -dump $(DUMP) $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor > out1 2>> out1; true
	@./resources/binaries/corewar -d $(DUMP) $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor > out2; true
	@if diff out1 out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_VM_DIR)$(X)" $(EOC); \
		else echo $(RED) " - [KO] $(T_VM_DIR)$(X)" $(EOC) ; \
	fi

tests_vm_dump_overflow: corewar
	@echo $(CYAN) " - Test Overflow DUMP Case $(DUMP)" $(EOC)
	@$(foreach x, $(T_VM_FILES_O), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_O) test_vm_dump_overflow;)

NUMBERS = 1 20 50 80 150 200 600 800 1400 2400 5000 8000 10000 50000
tests_vm_dump_overflow_loop: corewar
	@$(foreach x, $(NUMBERS), $(MAKE) DUMP=$x T_VM_DIR=$(T_VM_DIR_O)  SILENT='> /dev/null' tests_vm_dump_overflow;)

test_vm_op_overflow : corewar
	@./resources/binaries/asm $(T_VM_DIR)$(X).s > /dev/null; true
	@./corewar -v 30 $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor > out1 2>> out1; true
	@./resources/binaries/corewar -v 30 -a $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor > out2; true
	@if diff out1 out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_VM_DIR)$(X)" $(EOC); \
		else echo $(RED) " - [KO] $(T_VM_DIR)$(X)" $(EOC) ; \
	fi

tests_vm_op_overflow: corewar
	@echo $(CYAN) " - Test Overflow Op Case" $(EOC)
	@$(foreach x, $(T_VM_FILES_O), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_O) SILENT='> /dev/null' test_vm_op_overflow;)

T_VM_DIR_ERROR = tests/vm/error/
T_VM_FILES_ERROR:=$(shell cd $(T_VM_DIR_ERROR); ls | egrep '^[^X]+$$' | rev | cut -f 2- -d '.' | rev | sort -f )

test_vm_error : corewar
	@./resources/binaries/asm $(T_VM_DIR_ERROR)$(X).s > /dev/null; true
	@if [[ $$(./corewar $(T_VM_DIR_ERROR)$(X).cor $(SILENT) ) < 0 ]] ; \
		then echo $(GREEN) " - [OK] $(T_VM_DIR_ERROR)$(X)" $(EOC); \
		else echo $(RED) " - [KO] $(T_VM_DIR_ERROR)$(X)" $(EOC) ; \
	fi

tests_vm_error: corewar
	@echo $(CYAN) " - Test VM Error Cases" $(EOC)
	@$(foreach x, $(T_VM_FILES_ERROR), $(MAKE) X=$x test_vm_error;)

tests_vm: corewar
	@echo $(CYAN) " - Test Virtual Machine" $(EOC)
	@$(MAKE) tests_vm_error SILENT='2> /dev/null'
	@$(MAKE) tests_vm_op
	@$(MAKE) tests_vm_dump
	@$(MAKE) tests_vm_battle
	@$(MAKE) tests_vm_dump_overflow
	@$(MAKE) tests_vm_op_overflow
	
tests: tests_asm tests_vm

.PHONY: all clean fclean re assemble clean_cor debug norm norm2 tests tests_asm test_asm_leak tests_asm_leak tests_asm_valid tests_asm_error tests_asm_v libft
