/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <jyeo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:40:47 by jyeo              #+#    #+#             */
/*   Updated: 2018/04/18 07:43:56 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct		s_param
{
	char			*name;
	unsigned char	*memory;
	int				memory_size;
}					t_param;

typedef struct		s_code
{
	char			*line;
	char			*hex;
	char			*label;
	char			*opr;
	char			ocp;
	int				bit_size;
	int				bit_location;
	struct	s_param	param_a;
	struct	s_param	param_b;
	struct	s_param	param_c;
	struct	s_code	*next;
}					t_code;

int		ft_find_index(const char **arr, char *str)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i],str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void		ft_process_param(t_code **list, char *str, int nb_param)
{
	int		size;
	unsigned char	ocp;
	const char	*d_4[7] = {"live", "ld", "and", "or","xor", "lld", 0};


	ocp = 0;
	size = 0;
	if (str[0] == 'r')
	{
		ocp += 1 << (nb_param * 2);
		size = 1;
	}
	else if (str[0] == '%')
	{
		ocp += 2 << (nb_param * 2);
		if (ft_find_index(d_4, (*list)->opr) == -1)
			size = 2;
		else
			size = 4;
	}
	else
	{
		ocp += 3 << (nb_param * 2);
		size = 2;
	}
	if ((*list)->ocp != -1)
		(*list)->ocp += ocp;
	(*list)->bit_size += size;
	if (nb_param == 3)
	{
		(*list)->param_a.memory = (unsigned char *)malloc(sizeof(unsigned char) * size);
		ft_memset((void *)(*list)->param_a.memory, 0, size);
		(*list)->param_a.memory_size = size;
	}
	else if (nb_param == 2)
	{
		(*list)->param_b.memory = (unsigned char *)malloc(sizeof(unsigned char) * size);
		ft_memset((void *)(*list)->param_b.memory, 0, size);
		(*list)->param_b.memory_size = size;
	}
	else if (nb_param == 1)
	{
		(*list)->param_c.memory = (unsigned char *)malloc(sizeof(unsigned char) * size);
		ft_memset((void *)(*list)->param_c.memory, 0, size);
		(*list)->param_c.memory_size = size;
	}
}

t_code		*ft_get_operation(t_code **list, char *str)
{
	t_code	*lst;

	lst = *list;
	while (lst)
	{
		if (lst->label != NULL)
		{
			if (ft_strcmp(lst->label, str) == 0)
				return (lst);
		}
		
		lst = lst->next;
	}
	return (lst);
}

int		ft_get_label_location(t_code **list, char *str)
{
	t_code *lst;

	lst = *list;
	while (lst)
	{
		if (lst->label != NULL)
		{
			if (ft_strcmp(lst->label, str) == 0)
				return (lst->bit_location);
		}
		lst = lst->next;
	}
	return (0);
}

int		ft_calc_value(t_code **list, t_code **lst, t_param *param)
{
	int		value;
	int		label_location;
	if ((*param).name[0] == 'r')
	{
		value = ft_atoi((*param).name + 1);
	}
	else if ((*param).name[0] == '%')
	{
		if ((*param).name[1] == ':')
		{
			label_location = ft_get_label_location(list, (*param).name + 2);
			value = label_location - (*lst)->bit_location;
		}
		else
			value = ft_atoi((*param).name + 1);
	}
	else
	{
		if ((*param).name[0] == ':')
		{
			label_location = ft_get_label_location(list, (*param).name + 1);
			value = label_location - (*lst)->bit_location;
		}
		else
			value = ft_atoi((*param).name);
		
	}
	return (value);
}

void		ft_get_value(t_code **list, t_code **lst)
{
	int value;
	int i;
	if ((*lst)->param_a.name != NULL)
	{
		value = ft_calc_value(list, lst, &(*lst)->param_a);
		i = ((*lst)->param_a.memory_size - 1);
		while (i >= 0)
		{
			(*lst)->param_a.memory[i] = (*lst)->param_a.memory[i] | (value >> (8 * i));
			i--;
		}
		
	}
	if ((*lst)->param_b.name != NULL)
	{
		value = ft_calc_value(list, lst, &(*lst)->param_b);
		i = ((*lst)->param_b.memory_size - 1);
		while (i >= 0)
		{
			(*lst)->param_b.memory[i] = (*lst)->param_b.memory[i] | (value >> (8 * i));
			i--;
		}
	}
	if ((*lst)->param_c.name != NULL)
	{
		value = ft_calc_value(list, lst, &(*lst)->param_c);
		i = ((*lst)->param_c.memory_size - 1);
		while (i >= 0)
		{
			(*lst)->param_c.memory[i] = (*lst)->param_c.memory[i] | (value >> (8 * i));
			i--;
		}
	}
}

void	ft_fill_hex(t_code **list)
{
	int		i;
	char	*hex;
	char	*convert;
	char	*tmp;
	const char 	*op[17] = {"live", "ld", "st", "add", "sub", "add", "or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff", 0};


	hex = ft_strnew(0);
	convert = ft_itoa_base(ft_find_index(op, (*list)->opr) + 1, 16);
	if (ft_strlen(convert) < 2)
	{
		tmp = hex;
		hex = ft_strjoin(hex, "0");
		free(tmp);
	}
	tmp = hex;
	hex = ft_strjoin(hex, convert);
	free(tmp);
	free(convert);
	if ((*list)->ocp != -1)
	{
		tmp = hex;
		hex = ft_strjoin(hex, ft_itoa_base((*list)->ocp, 16));
		free(tmp);
	}
	if ((*list)->param_a.name != NULL)
	{
		i = ((*list)->param_a.memory_size - 1);
		while (i >= 0)
		{
			convert = ft_itoa_base((*list)->param_a.memory[i], 16);
			if (ft_strlen(convert) < 2)
			{
				tmp = hex;
				hex = ft_strjoin(hex, "0");
				free(tmp);
			}
			tmp = hex;
			hex = ft_strjoin(hex, convert);
			free(tmp);
			free(convert);
			i--;
		}
	}
	if ((*list)->param_b.name != NULL)
	{
		i = ((*list)->param_b.memory_size - 1);
		while (i >= 0)
		{
			convert = ft_itoa_base((*list)->param_b.memory[i], 16);
			if (ft_strlen(convert) < 2)
			{
				tmp = hex;
				hex = ft_strjoin(hex, "0");
				free(tmp);
			}
			tmp = hex;
			hex = ft_strjoin(hex, convert);
			free(tmp);
			free(convert);
			i--;
		}
	}
	if ((*list)->param_c.name != NULL)
	{
		i = ((*list)->param_c.memory_size - 1);
		while (i >= 0)
		{
			convert = ft_itoa_base((*list)->param_c.memory[i], 16);
			if (ft_strlen(convert) < 2)
			{
				tmp = hex;
				hex = ft_strjoin(hex, "0");
				free(tmp);
			}
			tmp = hex;
			hex = ft_strjoin(hex, convert);
			free(tmp);
			free(convert);
			i--;
		}
	}
	(*list)->hex = ft_strdup(hex);
	free(hex);
}

void	ft_convert(t_code **list)
{
	t_code	*lst;
	char	**split;
	int		bit_location;
	int		i;
	int		phase;
	int		ocp;
	const char 	*op[17] = {"live", "ld", "st", "add", "sub", "add", "or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff", 0};
	const char	*non_ocp[5] = {"live", "zjmp", "fork", "lfork", 0};

	lst = *list;
	bit_location = 0;
	while (lst)
	{
		phase = 0;
		if (lst->line[0] != '.' && lst->line[0] && lst->line[0] != '#')
		{
			split = ft_strsplit(lst->line, ' ');
			i = 0;
			ocp = 0;
			lst->bit_size = 1;
			lst->ocp = 0;
			lst->bit_location = bit_location;
			while (split[i])
			{
				if (split[i][0] == ';' || split[i][0] == '#')
					break ;
				if (phase == 0)
				{
					if (split[i][ft_strlen(split[i]) - 1] == ':')
					{
						split[i][ft_strlen(split[i]) - 1] = '\0';
						lst->label = ft_strdup(split[i]);
					}
					if ((ft_find_index(op, split[i])) != -1)
					{
						lst->opr = ft_strdup(split[i]);
						if (ft_find_index(non_ocp, split[i]) == -1)
							lst->bit_size++;
						else
							lst->ocp = -1;
						phase = 1;
					}
				}
				else if (phase == 1)
				{
					if (split[i][ft_strlen(split[i]) - 1] == ',')
						split[i][ft_strlen(split[i]) - 1] = '\0';
					if (lst->param_a.name == NULL)
					{
						lst->param_a.name = ft_strdup(split[i]);
						ft_process_param(&lst, split[i], 3);
					}
					else if (lst->param_b.name == NULL)
					{
						lst->param_b.name = ft_strdup(split[i]);
						ft_process_param(&lst, split[i], 2);
					}
					else if (lst->param_c.name == NULL)
					{
						lst->param_c.name = ft_strdup(split[i]);
						ft_process_param(&lst, split[i], 1);
					}
				}
				i++;
			}
			bit_location += lst->bit_size;
		}
		lst = lst->next;
	}
	lst = *list;
	while (lst)
	{
		if (lst->line[0] != '.' && lst->line[0] && lst->line[0] != '#')
		{
			ft_get_value(list, &lst);
			ft_fill_hex(&lst);
			
			ft_printf("%d (%d) : %s %s ocp: %d\n", lst->bit_location, lst->bit_size, lst->label, lst->opr, lst->ocp);
			ft_printf("\t %s %s %s \n", lst->param_a.name, lst->param_b.name, lst->param_c.name);
			ft_printf("\t %s \n", lst->hex);
		}
		lst = lst->next;
	}
}
/*
**	ft_reverse_list will reverse the order of the list
**
*/
void	ft_reverse_list(t_code **list)
{
	t_code	*buff;
	t_code	*tmp;
	t_code	*lst;

	buff = NULL;
	lst = *list;
	while (lst)
	{
		tmp = lst->next;
		lst->next = buff;
		buff = lst;
		lst = tmp;
	}
	*list = buff;
}

void	ft_parse(t_code **list, char *line)
{
	t_code *node;

	node = (t_code *)malloc(sizeof(t_code));
	node->line = ft_strdup(line);
	node->label = NULL;
	node->param_a.name = NULL;
	node->param_b.name = NULL;
	node->param_c.name = NULL;
	node->opr = NULL;
	node->bit_size = 0;
	node->bit_location = 0;
	node->ocp = 0;
	if (!(*list))
		*list = node;
	else
	{
		node->next = *list;
		*list = node;
	}
}

int		main()
{
	int		fd;
	char	*line;
	t_code	*list;

	list = NULL;
	fd = open("test.s", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_parse(&list, line);
		free(line);
	}
	close(fd);
	ft_reverse_list(&list);
	ft_convert(&list);
	return (0);
}