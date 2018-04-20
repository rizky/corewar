/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:39:11 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/20 15:52:25 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VM_H
# define FT_VM_H

# include "libft.h"
# include "op.h"

# define OPT_D 0
# define OPT_S 1
# define OPT_V 2
# define OPT_B 3
# define OPT_N 4
# define OPT_A 5

# define OPT_NUM 6

typedef struct	s_vm
{
	///OPTIONS///
	int			opt[OPT_NUM];
	int			d_cy; 		//cycles
	int			s_cy;		//cycles
	int			v_lvl;		//verbosity level
	int			stealth;
	/////////////
}				t_vm;

int		vm_options(char **av, t_vm *v);
void	vm_print(void);

#endif
