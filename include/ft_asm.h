/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:46:13 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/21 22:14:03 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ASM_H
# define FT_ASM_H

#include	"op.h"
#include	"libft.h"

typedef struct		s_asm_code
{
	char			*code;
	int				*param;
	int				nb_param;
	void			*function;
}					t_asm_code;

#endif