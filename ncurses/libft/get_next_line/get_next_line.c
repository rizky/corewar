/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 23:43:06 by jyeo              #+#    #+#             */
/*   Updated: 2017/11/25 23:43:08 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	ft_remove_list(int fd, t_line **list)
{
	t_line			*lst;
	t_line			*prev;

	lst = *list;
	prev = NULL;
	if (lst != NULL && lst->fd == fd)
	{
		*list = lst->next;
		FREE(lst);
		return ;
	}
	while (lst && lst->fd != fd)
	{
		prev = lst;
		lst = lst->next;
	}
	prev->next = lst->next;
	FREE(lst);
}

static	t_line	*ft_fetch_list(t_line **list, int fd)
{
	t_line			*lst;
	t_line			*new;

	lst = *list;
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	if (!lst)
	{
		ERROR((new = (t_line *)malloc(sizeof(t_line))) == NULL, NULL);
		new->fd = fd;
		new->n_line = NULL;
		new->next = *list;
		*list = new;
	}
	return (*list);
}

static	char	*ft_get_line(char **next_line)
{
	int				i;
	char			*tmp;
	char			*line;

	i = 0;
	line = NULL;
	while ((*next_line)[i] && (*next_line)[i] != '\n')
		i++;
	FERROR((tmp = ft_strsub(*next_line, 0, i)) == NULL, *next_line, NULL);
	FERROR((line = ft_strdup(tmp)) == NULL, tmp, NULL);
	FREE(tmp);
	if ((*next_line)[i] != '\0')
		i++;
	tmp = *next_line;
	FERROR((*next_line = ft_strdup(*next_line + i)) == NULL, tmp, NULL);
	FREE(tmp);
	return (line);
}

static	int		ft_get(const int fd, char *buf, char **next_line)
{
	int				ret;
	char			*tmp;

	if (!(*next_line) || **next_line == '\0')
	{
		tmp = *next_line;
		ERROR((*next_line = ft_strnew(0)) == NULL, -1);
		if (**next_line == '\0')
			FREE(tmp);
	}
	while (!(ft_strchr(buf, '\n')))
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			tmp = *next_line;
			FERROR((*next_line = ft_strjoin(*next_line, buf)) == NULL, tmp, -1);
			FREE(tmp);
		}
		else if (ret == 0)
			return (0);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			*buf;
	t_line			*lst;
	static t_line	*list;

	ERROR((buf = ft_strnew(BUFF_SIZE)) == NULL, -1);
	if (fd == -1 || (read(fd, buf, 0)) == -1 || !line)
	{
		FREE(buf);
		return (-1);
	}
	ERROR((lst = ft_fetch_list(&list, fd)) == NULL, -1);
	FERROR((ft_get(fd, buf, &lst->n_line)) == -1, list, -1);
	FREE(buf);
	if (*lst->n_line != '\0')
		ERROR((*line = ft_get_line(&lst->n_line)) == NULL, -1);
	else
	{
		FREE(lst->n_line);
		ft_remove_list(fd, &list);
		return (0);
	}
	return (1);
}
