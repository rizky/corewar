/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:39:11 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/24 18:55:26 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VM_H
# define FT_VM_H

# include "libft.h"
# include "op.h"

# define V_LVL_0 0
# define V_LVL_1 1
# define V_LVL_2 2
# define V_LVL_4 3
# define V_LVL_8 4
# define V_LVL_16 5

typedef struct	s_vm
{
	int			dump;
	int			cycles;
	int			v_lvl[6];
	char		*players[MAX_PLAYERS + 2];
}				t_vm;

int				vm_options(char **av, t_vm *vm);
int				vm_print_usage(char **av, int status);
void			vm_print(t_vm vm);

int				vm_valid_verbosity_lvl(int lvl);
int				vm_lvl_to_index(int index);
int				ft_isnumber(char *str);
int				ft_abs(int i);

#endif
