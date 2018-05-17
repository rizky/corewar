# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/01 20:07:00 by rnugroho          #+#    #+#              #
#    Updated: 2018/05/17 21:41:34 by rnugroho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----- Config -----

ASM_PATH:=./corewar-project/asm
VM_PATH:=./corewar-project/corewar

OPT_V:=-v 30
OPT_A:=-a
OPT_DUMP:=-dump

# ----- Colors -----
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
CYAN:="\033[1;35m"
PURPLE:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"
# ==================
TALLY:=.tally

all: tests

clean:
	@rm -f out1 out2

clean_tally:
	@rm -f $(TALLY)

# ----- TEST UNIT ASM ------
T_ASM_DIR_ERROR = tests/asm/error/
T_ASM_FILES_ERROR:=$(shell cd $(T_ASM_DIR_ERROR); ls  | egrep '^$(T_FILE_ERROR).*.s$$' | sort -f )

test_asm_error :
	@if [[ $$(./$(ASM_PATH) $(OPT_A) $(T_ASM_DIR_ERROR)$(X) $(SILENT) ) < 0 ]] ; \
		then echo $(GREEN) " - [OK] $(T_ASM_DIR_ERROR)$(X)" $(EOC) && echo "OK" >> $(TALLY); \
		else echo $(RED) " - [KO] $(T_ASM_DIR_ERROR)$(X)" $(EOC) && echo "KO" >> $(TALLY); \
	fi

tests_asm_error:
	@echo $(CYAN) " - Test Error Cases" $(EOC)
	@$(foreach x, $(T_ASM_FILES_ERROR), $(MAKE) X=$x test_asm_error;)

T_ASM_DIR_VALID = tests/asm/valid/
T_ASM_DIR_VALID_2 = tests/asm/valid2/
T_ASM_FILES_VALID:=$(shell cd $(T_ASM_DIR_VALID); ls  | egrep '^.*.s$$' | sort -f )
T_ASM_FILES_BIN:=$(shell cd $(T_ASM_DIR_VALID); ls | egrep '^.*.s$$' | rev | cut -f 2- -d '.' | rev | sort -f )

test_asm_bin:
	@./$(ASM_PATH) $(T_ASM_DIR_VALID)$(X).s $(SILENT) ; true
	@./binaries/asm $(T_ASM_DIR_VALID_2)$(X).s $(SILENT) ; true
	@if diff $(T_ASM_DIR_VALID)$(X).cor $(T_ASM_DIR_VALID_2)$(X).cor $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_ASM_DIR_VALID)$(X).cor" $(EOC); \
		else echo $(RED) " - [KO] $(T_ASM_DIR_VALID)$(X).cor" $(EOC) ; \
	fi

tests_asm_bin:
	@echo $(CYAN) " - Test Binary Files" $(EOC)
	@$(foreach x, $(T_ASM_FILES_BIN), $(MAKE) X=$x test_asm_bin;)

test_asm_valid :
	@./$(ASM_PATH) $(OPT_A) $(T_ASM_DIR_VALID)$(X) > out1 2>> out1; true
	@./binaries/asm -a $(T_ASM_DIR_VALID)$(X) > out2; true
	@if diff out1 out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_ASM_DIR_VALID)$(X)" $(EOC) && echo "OK" >> $(TALLY); \
		else echo $(RED) " - [KO] $(T_ASM_DIR_VALID)$(X)" $(EOC) && echo "KO" >> $(TALLY); \
	fi

tests_asm_valid:
	@echo $(CYAN) " - Test Valid Cases" $(EOC)
	@$(foreach x, $(T_ASM_FILES_VALID), $(MAKE) X=$x test_asm_valid;)

tests_asm_v: tests_asm_valid tests_asm_error tests_asm_bin

tests_asm:
	@echo $(CYAN) " - Test Assembler" $(EOC)
	@$(MAKE) tests_asm_valid SILENT='> /dev/null'
	@$(MAKE) tests_asm_error SILENT='2> /dev/null'
	@$(MAKE) tests_asm_bin SILENT='> /dev/null'

test_asm_leak:
	@valgrind ./$(ASM_PATH) $(X) 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*|Invalid read.*'

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

test_vm_op :
	@./binaries/asm $(T_VM_DIR)$(X).s > /dev/null; true
	@./$(VM_PATH) $(OPT_V) $(T_VM_DIR)$(X).cor > out1 2>> out1; true
	@./binaries/corewar $(OPT_V) -a $(T_VM_DIR)$(X).cor > out2; true
	@if diff out1 out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_VM_DIR)$(X)" $(EOC) && echo "OK" >> $(TALLY); \
		else echo $(RED) " - [KO] $(T_VM_DIR)$(X)" $(EOC) && echo "KO" >> $(TALLY); \
	fi

tests_vm_op:
	@echo $(CYAN) " - Test Basic Operations" $(EOC)
	@$(foreach x, $(T_VM_FILES_OP), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_OP) test_vm_op;)

tests_vm_dump_champs:
	@echo $(CYAN) " - Test Memory Dump on Champs $(DUMP)" $(EOC)
	@$(foreach x, $(T_VM_FILES_C), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_C) test_vm_dump;)

NUMBERS = 1 20 50 80 150 200 600 800 1400 2400 5000 8000 10000 50000
tests_vm_dump_champs_loop:
	@$(foreach x, $(NUMBERS), $(MAKE) DUMP=$x T_VM_DIR=$(T_VM_DIR_C) tests_vm_dump_champs;)

test_vm_op_champ :
	@./binaries/asm $(T_VM_DIR)$(X).s > /dev/null; true
	@./$(VM_PATH) $(OPT_V) $(T_VM_DIR)$(X).cor > $(T_VM_DIR)$(X).out1 2>> $(T_VM_DIR)$(X).out1; true
	@./binaries/corewar $(OPT_V) -a $(T_VM_DIR)$(X).cor > $(T_VM_DIR)$(X).out2; true
	@if diff $(T_VM_DIR)$(X).out1 $(T_VM_DIR)$(X).out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_VM_DIR)$(X)" $(EOC) && rm $(T_VM_DIR)$(X).out1 $(T_VM_DIR)$(X).out2 && echo "OK" >> $(TALLY); \
		else echo $(RED) " - [KO] $(T_VM_DIR)$(X)" $(EOC) && echo "KO" >> $(TALLY) && diff $(T_VM_DIR)$(X).out1 $(T_VM_DIR)$(X).out2 | head -20; \
	fi

tests_vm_op_champs:
	@echo $(CYAN) " - Test Basic Operations on Champs" $(EOC)
	@$(foreach x, $(T_VM_FILES_C), ($(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_C) SILENT='> /dev/null' test_vm_op_champ;)&)

tests_vm_ocp:
	@echo $(CYAN) " - Test Basic Operations on Champs" $(EOC)
	@$(foreach x, $(T_VM_FILES_OCP), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_OCP) test_vm_op;)

test_vm_dump :
	@./binaries/asm $(T_VM_DIR)$(X).s > /dev/null; true
	@./$(VM_PATH) $(OPT_DUMP) $(DUMP) $(T_VM_DIR)$(X).cor > out1 2>> out1; true
	@./binaries/corewar -d $(DUMP) $(T_VM_DIR)$(X).cor > out2; true
	@if diff out1 out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_VM_DIR)$(X)" $(EOC) && echo "OK" >> $(TALLY); \
		else echo $(RED) " - [KO] $(T_VM_DIR)$(X)" $(EOC) && echo "KO" >> $(TALLY); \
	fi

tests_vm_dump:
	@echo $(CYAN) " - Test Memory Dump $(DUMP)" $(EOC)
	@$(foreach x, $(T_VM_FILES_OP), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_OP) test_vm_dump;)

NUMBERS = 1 20 50 80 150 200 600 800 1400 2400 5000 8000 10000 20000
tests_vm_dump_loop:
	@$(foreach x, $(NUMBERS), $(MAKE) DUMP=$x T_VM_DIR=$(T_VM_DIR_OP) tests_vm_dump;)

test_vm_leak:
	@valgrind ./$(VM_PATH) $(X) 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*|Invalid read.*'

tests_vm_leak:
	@echo $(CYAN) " - Test Leaks" $(EOC)
	@$(foreach x, $(T_VM_FILES_ERROR), $(MAKE) X=$(T_VM_DIR_ERROR)$(x) test_vm_leak;)
	@$(foreach x, $(T_VM_FILES_OP), $(MAKE) X=$(T_VM_DIR_OP)$(x) test_vm_leak;)
	@$(foreach x, $(T_VM_FILES_B), $(MAKE) X=$(T_VM_DIR_B)$(x) test_vm_leak;)
	@$(foreach x, $(T_VM_FILES_C), $(MAKE) X=$(T_VM_DIR_C)$(x) test_vm_leak;)
	@valgrind ./$(VM_PATH) -n2 $(T_VM_DIR_C)zork.cor $(T_VM_DIR_ERROR)magic_number.cor 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*|Invalid read.*'
	@valgrind ./$(VM_PATH) -n2 $(T_VM_DIR_C)zork.cor 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*|Invalid read.*'
	@valgrind ./$(VM_PATH) -u $(T_VM_DIR_OP)add.cor 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*|Invalid read.*'
	@valgrind ./$(VM_PATH) $(T_VM_DIR_OP)add.cor 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*|Invalid read.*'
	@valgrind ./$(VM_PATH) $(OPT_DUMP) 150 $(T_VM_DIR_OP)add.cor 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*|Invalid read.*'
	@valgrind ./$(VM_PATH) $(OPT_V) $(T_VM_DIR_OP)add.cor 2>&1 | grep -oE 'Command:.*|definitely.*|indirectly.*|Invalid read.*'

T_VM_DIR_B = tests/vm/battle/
T_VM_FILES_B:=$(shell cd $(T_VM_DIR_B); ls | egrep '^$(T_FILE).*.s$$' | egrep '^[^X]+.s$$' | rev | cut -f 2- -d '.' | rev | sort -f )

test_vm_battle :
	@./binaries/asm $(T_VM_DIR_B)$(X).s > /dev/null; true
	@./binaries/asm $(T_VM_DIR_B)$(X)X.s > /dev/null; true
	@./$(VM_PATH) -v30 $(T_VM_DIR_B)$(X).cor $(T_VM_DIR_B)$(X)X.cor > out1 2>> out1; true
	@./binaries/corewar $(OPT_V) -a $(T_VM_DIR_B)$(X).cor $(T_VM_DIR_B)$(X)X.cor > out2; true
	@if diff out1 out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_VM_DIR_B)$(X)" $(EOC) && echo "OK" >> $(TALLY); \
		else echo $(RED) " - [KO] $(T_VM_DIR_B)$(X)" $(EOC) && echo "KO" >> $(TALLY); \
	fi

tests_vm_battle:
	@echo $(CYAN) " - Test Battle" $(EOC)
	@$(foreach x, $(T_VM_FILES_B), $(MAKE) X=$x test_vm_battle;)

T_VM_DIR_O = tests/vm/overflow/
T_VM_FILES_O:=$(shell cd $(T_VM_DIR_O); ls | egrep '^$(T_FILE).*.s$$' | rev | cut -f 2- -d '.' | rev | sort -f )

test_vm_dump_overflow :
	@./binaries/asm $(T_VM_DIR)$(X).s > /dev/null; true
	@./$(VM_PATH) $(OPT_DUMP) $(DUMP) $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor > out1 2>> out1; true
	@./binaries/corewar -d $(DUMP) $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor > out2; true
	@if diff out1 out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_VM_DIR)$(X)" $(EOC) && echo "OK" >> $(TALLY); \
		else echo $(RED) " - [KO] $(T_VM_DIR)$(X)" $(EOC) && echo "KO" >> $(TALLY); \
	fi

tests_vm_dump_overflow: 
	@echo $(CYAN) " - Test Overflow DUMP Case $(DUMP)" $(EOC)
	@$(foreach x, $(T_VM_FILES_O), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_O) test_vm_dump_overflow;)

NUMBERS = 1 20 50 80 150 200 600 800 1400 2400 5000 8000 10000 50000
tests_vm_dump_overflow_loop: 
	@$(foreach x, $(NUMBERS), $(MAKE) DUMP=$x T_VM_DIR=$(T_VM_DIR_O)  SILENT='> /dev/null' tests_vm_dump_overflow;)

test_vm_op_overflow : 
	@./binaries/asm $(T_VM_DIR)$(X).s > /dev/null; true
	@./$(VM_PATH) $(OPT_V) $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor > out1 2>> out1; true
	@./binaries/corewar $(OPT_V) -a $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor $(T_VM_DIR)$(X).cor > out2; true
	@if diff out1 out2 $(SILENT); \
		then echo $(GREEN) " - [OK] $(T_VM_DIR)$(X)" $(EOC) && echo "OK" >> $(TALLY); \
		else echo $(RED) " - [KO] $(T_VM_DIR)$(X)" $(EOC) && echo "KO" >> $(TALLY); \
	fi

tests_vm_op_overflow: 
	@echo $(CYAN) " - Test Overflow Op Case" $(EOC)
	@$(foreach x, $(T_VM_FILES_O), $(MAKE) X=$x T_VM_DIR=$(T_VM_DIR_O) SILENT='> /dev/null' test_vm_op_overflow;)

T_VM_DIR_ERROR = tests/vm/error/
T_VM_FILES_ERROR:=$(shell cd $(T_VM_DIR_ERROR); ls | egrep '^[^X]+$$' | rev | cut -f 2- -d '.' | rev | sort -f )

test_vm_error : 
	@./binaries/asm $(T_VM_DIR_ERROR)$(X).s > /dev/null; true
	@if [[ $$(./$(VM_PATH) $(T_VM_DIR_ERROR)$(X).cor $(SILENT) ) < 0 ]] ; \
		then echo $(GREEN) " - [OK] $(T_VM_DIR_ERROR)$(X)" $(EOC) && echo "OK" >> $(TALLY); \
		else echo $(RED) " - [KO] $(T_VM_DIR_ERROR)$(X)" $(EOC) && echo "KO" >> $(TALLY); \
	fi

tests_vm_error: 
	@echo $(CYAN) " - Test VM Error Cases" $(EOC)
	@$(foreach x, $(T_VM_FILES_ERROR), $(MAKE) X=$x test_vm_error;)

tests_vm: 
	@echo $(CYAN) " - Test Virtual Machine" $(EOC)
	@$(MAKE) tests_vm_error SILENT='2> /dev/null'
	@$(MAKE) tests_vm_op
	@$(MAKE) tests_vm_dump
	@$(MAKE) tests_vm_battle
	@$(MAKE) tests_vm_dump_overflow
	@$(MAKE) tests_vm_op_overflow

SCORE=`grep "OK" $(TALLY) | wc -l`

TOTAL=`grep "K" $(TALLY) | wc -l`

tests: clean_tally tests_asm tests_vm
	@if [[ $(SCORE) = $(TOTAL) ]] ; \
		then echo $(GREEN) ; \
	fi
	@if [[ $(SCORE) -lt $(TOTAL) ]] ; \
		then echo $(CYAN) ; \
	fi
	@if [[ $(SCORE) -lt $$(($(TOTAL) / 2)) ]] ; \
		then echo $(RED) ; \
	fi
	@echo " " - [$(SCORE) / $(TOTAL) ] $(EOC)
	@rm -f $(TALLY)

tests_leaks: tests_asm_leak tests_vm_leak

test: tests

.PHONY: all clean test tests tests_leaks tests_asm test_asm_leak tests_asm_leak test_asm_valid tests_asm_valid test_asm_bin tests_asm_bin tests_asm_v tests_asm_error tests_asm_v tests_vm test_vm_leak tests_vm_leak test_vm_battle tests_vm_battle test_vm_dump tests_vm_dump tests_vm_dump_champs tests_vm_dump_champs_loop tests_vm_dump_loop test_vm_dump_overflow tests_vm_dump_overflow tests_vm_dump_overflow_loop tests_vm_ocp test_vm_op tests_vm_op test_vm_op_champ tests_vm_op_champs test_vm_op_overflow tests_vm_op_overflow test_vm_error tests_vm_error libft
