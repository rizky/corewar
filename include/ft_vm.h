/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:39:11 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/23 16:08:46 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VM_H
# define FT_VM_H

# include "libft.h"
# include "op.h"

# define OPT_D 0
# define OPT_V 1

# define OPT_NUM 3
# define OPT_STR "dv"
# define OPT_STR_V "d"

# define MALLOC			1
# define INVALID_FILE	2
# define CHAMP_MAX		3
# define CODE_MAX		4

typedef struct	s_op_dict
{
	char		*name;
	int			opcode;
	int			d_size;
	int			param_c;
	int			is_oc;
	int			p_type[3];
	void		*opfunc;
}				t_op_dict;

typedef struct	s_process
{
	int			offset;
	int			pc;
	int			live_nbr;
}				t_process;

typedef struct	s_champ
{
	t_header	header;
	char		*op;
	t_array		*processes;
}				t_champ;

typedef struct	s_vm
{
	int			cycles;
	int			cycles_to_die;
	int			check_nbr;
	int			carrier;
	t_champ		champ[4];
	int			champ_size;
}				t_vm;

unsigned char	g_memory[MEM_SIZE];
unsigned char	g_memory_mark[MEM_SIZE];

void			vm_print_verbose(t_vm vm, int i);
int				vm_print_usage(char **av, int status);

int				vm_error(int errnum, int status);
int				vm_getoptions(char **av, int opt[OPT_NUM]);

int				vm_binary_toint(char *bin, int size);
int				vm_read_binary(int i, char **av, t_vm *vm);
void			vm_print_memory(unsigned char memory[MEM_SIZE]);
void			vm_print_memory_cursor(unsigned char memory[MEM_SIZE], t_vm vm);
void			vm_executor_process(t_vm *vm, t_process *p);
void			vm_executor(t_vm *vm);

void			vm_op_sti(t_vm *vm, t_process *p);
void			vm_op_and(t_vm *vm, t_process *p);
void			vm_op_zjmp(t_vm *vm, t_process *p);
void			vm_op_live(t_vm *vm, t_process *p);
void			vm_op_inc(t_vm *vm, t_process *p);

static	t_op_dict g_op_dict[17] = {
	{ .name = "\0", .opcode = 0x00, .d_size = 0, .param_c = 0, .is_oc = 0,
		{0, 0, 0}, &vm_op_inc},
	{ .name = "live", .opcode = 0x01, .d_size = 4, .param_c = 1, .is_oc = 0,
		{T_DIR, 0, 0}, &vm_op_inc},
	{ .name = "ld", .opcode = 0x02, .d_size = 4, .param_c = 2, .is_oc = 1,
		{T_DIR | T_IND, T_REG, 0}, &vm_op_inc},
	{ .name = "st", .opcode = 0x03, .d_size = 0, .param_c = 2, .is_oc = 1,
		{T_REG, T_REG | T_IND, 0}, &vm_op_inc},
	{ .name = "add", .opcode = 0x04, .d_size = 0, .param_c = 3, .is_oc = 1,
		{T_REG, T_REG, T_REG}, &vm_op_inc},
	{ .name = "sub", .opcode = 0x05, .d_size = 0, .param_c = 3, .is_oc = 1,
		{T_REG, T_REG, T_REG}, &vm_op_inc},
	{ .name = "and", .opcode = 0x06, .d_size = 4, .param_c = 3, .is_oc = 1,
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, &vm_op_inc},
	{ .name = "or", .opcode = 0x07, .d_size = 4, .param_c = 3, .is_oc = 1,
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, &vm_op_inc},
	{ .name = "xor", .opcode = 0x08, .d_size = 4, .param_c = 3, .is_oc = 1,
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, &vm_op_inc},
	{ .name = "zjmp", .opcode = 0x09, .d_size = 2, .param_c = 1, .is_oc = 0,
		{T_DIR, 0, 0}, &vm_op_inc},
	{ .name = "ldi", .opcode = 0x0a, .d_size = 2, .param_c = 3, .is_oc = 1,
		{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, &vm_op_inc},
	{ .name = "sti", .opcode = 0x0b, .d_size = 2, .param_c = 3, .is_oc = 1,
		{T_REG, T_REG | T_IND | T_DIR, T_DIR | T_REG}, &vm_op_sti},
	{ .name = "fork", .opcode = 0x0c, .d_size = 2, .param_c = 1, .is_oc = 0,
		{T_DIR, 0, 0}, &vm_op_inc},
	{ .name = "lld", .opcode = 0x0d, .d_size = 4, .param_c = 2, .is_oc = 1,
		{T_IND | T_DIR, T_REG, 0}, &vm_op_inc},
	{ .name = "lldi", .opcode = 0x0e, .d_size = 2, .param_c = 3, .is_oc = 1,
		{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, &vm_op_inc},
	{ .name = "lfork", .opcode = 0x0f, .d_size = 2, .param_c = 1, .is_oc = 0,
		{T_DIR, 0, 0}, &vm_op_inc},
	{ .name = "aff", .opcode = 0x10, .d_size = 0, .param_c = 1, .is_oc = 1,
		{T_REG, 0, 0}, &vm_op_inc}
};
#endif
