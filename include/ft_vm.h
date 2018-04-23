/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:39:11 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/23 15:41:00 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VM_H
# define FT_VM_H

# include "libft.h"
# include "op.h"

typedef struct	s_vm
{
	int			dump;
	int			cycles;
	int			verbose;
	int			verbosity_lvl;
	char		*players[MAX_PLAYERS + 2];
}				t_vm;

int				vm_options(char **av, t_vm *vm);
void			vm_print(t_vm vm);

int				vm_isnumber(char *str);

#endif
