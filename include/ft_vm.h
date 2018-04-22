/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:39:11 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/22 21:00:30 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VM_H
# define FT_VM_H

# include "libft.h"
# include "op.h"

# define OPT_D 0
# define OPT_N 1

# define OPT_NUM 2
# define OPT_STR "dn"

# define MALLOC			1
# define INVALID_FILE	2
# define CHAMP_MAX		3
# define CODE_MAX		4


typedef struct	s_champ
{
	char			*path;
	t_header		header;
	char			*op;
}				t_champ;


typedef struct	s_vm
{
	int				dump;
	int				cycles;
	t_champ			champ[4];
	int				champ_size;
}				t_vm;

void			vm_print_verbose(t_vm vm, int i);
int				vm_print_usage(char **av, int status);

int				vm_error(int errnum, int status);
int				vm_getoptions(char **av, int opt[OPT_NUM]);

int				vm_binary_toint(char *bin, int size);
int				vm_read_binary(int i, char **av, t_vm *vm);
void			vm_print_memory(unsigned char memory[MEM_SIZE]);
#endif
