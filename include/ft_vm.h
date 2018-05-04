/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:39:11 by rnugroho          #+#    #+#             */
/*   Updated: 2018/05/04 20:59:08 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VM_H
# define FT_VM_H

# include "libft.h"
# include "op.h"

# define MALLOC			1
# define CHAMP_MIN		2
# define CHAMP_MAX		3
# define INVALID_FILE	4
# define INVALID_HEADER	5
# define INVALID_MAGIC	6
# define INVALID_INSTR	7
# define CODE_MAX		8

# define V_LVL_0		0
# define V_LVL_1		1
# define V_LVL_2		2
# define V_LVL_4		3
# define V_LVL_8		4
# define V_LVL_16		5

typedef struct	s_param
{
	int			type;
	int			size;
	int			value;
}				t_param;

typedef struct	s_op
{
	int			opcode;
	int			oc;
	int			size;
	t_param		params[3];
	int			param_c;
}				t_op;

typedef struct	s_process
{
	int			offset;
	int			cycles;
	int			pc;
	int			pc_next;
	int			live_nbr;
	int			live_cycle;
	int			champ;
	int			carry;
	int			reg[REG_NUMBER + 1];
	t_op		op;
	int			index;
}				t_process;

typedef struct	s_champ
{
	t_header	header;
	char		*op;
	int			live_nbr;
}				t_champ;

typedef struct	s_vm
{
	int			valid_arg[2];
	int			dump;
	int			cycles;
	int			v_lvl[6];
	int			check_nbr;
	char		*players[MAX_PLAYERS + 1];
	t_champ		champ[4];
	t_array		processes;
	int			process_index;
	int			champ_size;
	int			last_dead_champ;
	int			last_live_champ;
	int			winner;
}				t_vm;

unsigned char	g_memory[MEM_SIZE];
unsigned char	g_memory_mark[MEM_SIZE];
int				g_cycles;
int				g_cycles_to;
int				g_cycles_to_die;
int				g_max_check;
int				g_live_nbr;

int				vm_options(char **av, t_vm *vm);
int				vm_print_usage(char **av, int status);
void			vm_init_g_var(void);

int				vm_error(int errnum, int status, char *name);

void			vm_free(t_vm *vm);
int				vm_free_err(t_vm *vm, int max, int errnum, char *file);

int				vm_binary_toint(unsigned char *bin, int size);
int				vm_read_binaries(char **paths, t_vm *vm);
void			*vm_memmark(void *dst, int i, size_t n);
void			vm_st_mem(int index, char *value, int champ, int size);
int				vm_ld_mem(int index, int size);

void			vm_decompiler(t_vm *vm);
void			vm_decompiler_param(t_process *p, t_op *op);

int				vm_checker(t_vm *vm);
int				vm_checker_livenbr(t_vm vm);

void			vm_executor(t_vm *vm);
int				vm_decompiler_op(t_vm *vm, t_process *p, t_op *op);

void			vm_print_memory(void);
void			vm_print_memory_color(t_vm vm);
void			vm_print_memory_cursor(t_vm vm);

char			*vm_to_big_endian(int value, int size);
void			vm_op_inc(t_vm *vm, t_process *p);
int				vm_checker_oc(t_op op);

void			vm_op_live(t_vm *vm, t_process *p);
void			vm_op_ld(t_vm *vm, t_process *p);
void			vm_op_st(t_vm *vm, t_process *p);
void			vm_op_add(t_vm *vm, t_process *p);
void			vm_op_sub(t_vm *vm, t_process *p);
void			vm_op_and(t_vm *vm, t_process *p);
void			vm_op_or(t_vm *vm, t_process *p);
void			vm_op_xor(t_vm *vm, t_process *p);
void			vm_op_zjmp(t_vm *vm, t_process *p);
void			vm_op_ldi(t_vm *vm, t_process *p);
void			vm_op_sti(t_vm *vm, t_process *p);
void			vm_op_fork(t_vm *vm, t_process *p);
void			vm_op_lld(t_vm *vm, t_process *p);
void			vm_op_lldi(t_vm *vm, t_process *p);
void			vm_op_lfork(t_vm *vm, t_process *p);
void			vm_op_aff(t_vm *vm, t_process *p);

void			vm_op_print(t_process p);
void			vm_live_print(t_process p);
void			vm_ld_print(t_process p);
void			vm_st_print(t_process p);
void			vm_add_print(t_process p);
void			vm_sub_print(t_process p);
void			vm_and_print(t_process p);
void			vm_or_print(t_process p);
void			vm_xor_print(t_process p);
void			vm_zjmp_print(t_process p);
void			vm_ldi_print(t_process p);
void			vm_sti_print(t_process p);
void			vm_fork_print(t_process p);
void			vm_lld_print(t_process p);
void			vm_lldi_print(t_process p);
void			vm_lfork_print(t_process p);
void			vm_aff_print(t_process p);

int				ft_init_param(t_process *p, int i);
int				ft_cursor(t_process *p, int param1, int param2, int i);

int				vm_valid_arg(char *arg, t_vm *vm);
int				vm_valid_verbosity_lvl(int lvl);
int				vm_lvl_to_index(int index);
int				ft_isnumber(char *str);
int				ft_abs(int i);

typedef struct	s_op_dict
{
	char		*name;
	int			opcode;
	int			d_size;
	int			param_c;
	int			is_oc;
	int			p_type[3];
	void		*opfunc;
	void		*opprint;
	int			is_car;
	int			cycles;
}				t_op_dict;

static	t_op_dict g_op_dict[17] = {
	{ .name = "\0", .opcode = 0x00, .d_size = 0, .param_c = 0, .is_oc = 0,
		{0, 0, 0}, &vm_op_inc, &vm_op_print, .is_car = 0, .cycles = 0},
	{ .name = "live", .opcode = 0x01, .d_size = 4, .param_c = 1, .is_oc = 0,
		{T_DIR, 0, 0}, &vm_op_live, &vm_live_print, .is_car = 0, .cycles = 10},
	{ .name = "ld", .opcode = 0x02, .d_size = 4, .param_c = 2, .is_oc = 1,
		{T_DIR | T_IND, T_REG, 0},
		&vm_op_ld, &vm_ld_print, .is_car = 1, .cycles = 5},
	{ .name = "st", .opcode = 0x03, .d_size = 4, .param_c = 2, .is_oc = 1,
		{T_REG, T_REG | T_IND, 0},
		&vm_op_st, &vm_st_print, .is_car = 0, .cycles = 5},
	{ .name = "add", .opcode = 0x04, .d_size = 4, .param_c = 3, .is_oc = 1,
		{T_REG, T_REG, T_REG},
		&vm_op_add, &vm_add_print, .is_car = 1, .cycles = 10},
	{ .name = "sub", .opcode = 0x05, .d_size = 4, .param_c = 3, .is_oc = 1,
		{T_REG, T_REG, T_REG},
		&vm_op_sub, &vm_sub_print, .is_car = 1, .cycles = 10},
	{ .name = "and", .opcode = 0x06, .d_size = 4, .param_c = 3, .is_oc = 1,
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		&vm_op_and, &vm_and_print, .is_car = 1, .cycles = 6},
	{ .name = "or", .opcode = 0x07, .d_size = 4, .param_c = 3, .is_oc = 1,
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		&vm_op_or, &vm_or_print, .is_car = 1, .cycles = 6},
	{ .name = "xor", .opcode = 0x08, .d_size = 4, .param_c = 3, .is_oc = 1,
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		&vm_op_xor, &vm_xor_print, .is_car = 1, .cycles = 6},
	{ .name = "zjmp", .opcode = 0x09, .d_size = 2, .param_c = 1, .is_oc = 0,
		{T_DIR, 0, 0},
		&vm_op_zjmp, &vm_zjmp_print, .is_car = 0, .cycles = 20},
	{ .name = "ldi", .opcode = 0x0a, .d_size = 2, .param_c = 3, .is_oc = 1,
		{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		&vm_op_ldi, &vm_ldi_print, .is_car = 0, .cycles = 25},
	{ .name = "sti", .opcode = 0x0b, .d_size = 2, .param_c = 3, .is_oc = 1,
		{T_REG, T_REG | T_IND | T_DIR, T_DIR | T_REG},
		&vm_op_sti, &vm_sti_print, .is_car = 0, .cycles = 25},
	{ .name = "fork", .opcode = 0x0c, .d_size = 2, .param_c = 1, .is_oc = 0,
		{T_DIR, 0, 0}, &vm_op_fork, &vm_fork_print, .is_car = 0, .cycles = 800},
	{ .name = "lld", .opcode = 0x0d, .d_size = 4, .param_c = 2, .is_oc = 1,
		{T_IND | T_DIR, T_REG, 0},
		&vm_op_lld, &vm_lld_print, .is_car = 1, .cycles = 10},
	{ .name = "lldi", .opcode = 0x0e, .d_size = 2, .param_c = 3, .is_oc = 1,
		{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		&vm_op_lldi, &vm_lldi_print, .is_car = 0, .cycles = 50},
	{ .name = "lfork", .opcode = 0x0f, .d_size = 2, .param_c = 1, .is_oc = 0,
		{T_DIR, 0, 0},
		vm_op_lfork, &vm_lfork_print, .is_car = 0, .cycles = 1000},
	{ .name = "aff", .opcode = 0x10, .d_size = 0, .param_c = 1, .is_oc = 1,
		{T_REG, 0, 0}, &vm_op_inc, &vm_aff_print, .is_car = 0, .cycles = 2}
};

#endif
