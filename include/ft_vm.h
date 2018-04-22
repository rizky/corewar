/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 21:39:11 by rnugroho          #+#    #+#             */
/*   Updated: 2018/04/22 15:08:59 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VM_H
# define FT_VM_H

# include "libft.h"
# include "op.h"

# define SOURCEFILE		1
# define MALLOC			2
# define INVALID_FILE	3
# define CHAMP_MAX		4

typedef struct	s_vm
{
	char			*path;
	int				dump;
	int				cycles;
	char			*players[MAX_PLAYERS + 2];
	t_header		header;
	char			*op;
}				t_vm;

int				vm_options(char **av, t_vm *v);
void			vm_print(t_vm vm);
int				vm_error(int errnum, int status);

#endif
