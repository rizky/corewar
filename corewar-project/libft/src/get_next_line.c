/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 18:00:07 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/16 18:53:23 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*handle_file(t_list **files, int fd)
{
	t_list	*file;
	t_file	f;

	file = *files;
	while (file)
	{
		if (((t_file*)((file->content)))->fd == fd)
			return (file);
		file = file->next;
	}
	f.fd = fd;
	f.content = ft_strnew(1);
	f.content_start = f.content;
	ft_lstadd((files), ft_lstnew((void*)&f, sizeof(t_file)));
	return (*files);
}

char	*retrive_line(char **content)
{
	char	*line;
	size_t	len;

	if (ft_strchr(*content, '\n'))
	{
		len = ft_strchr(*content, '\n') - *content;
		line = ft_strncpy(ft_strnew(len), *content, len);
		*content += (len + 1);
	}
	else
	{
		len = ft_strlen(*content);
		line = ft_strncpy(ft_strnew(len), *content, len);
		*content += len;
	}
	return (line);
}

int		get_next_line(int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	size_t			ret;
	static t_list	*files;
	t_list			*file;

	if ((fd < 0 || line == NULL || read(fd, buf, 0) < 0) || BUFF_SIZE < 1)
		return (-1);
	file = handle_file(&files, fd);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		ALLOCATED((GNL_CONTENT(file) = ft_strjoin(GNL_CONTENT(file), buf)));
		free(GNL_START(file));
		GNL_START(file) = GNL_CONTENT(file);
		if (ft_strchr(GNL_CONTENT(file), '\n'))
			break ;
	}
	if (ret < BUFF_SIZE && !ft_strlen(GNL_CONTENT(file)))
		return (0);
	ALLOCATED((*line = retrive_line(&GNL_CONTENT(file))));
	return (1);
}
