/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 15:05:47 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/07 05:15:13 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static t_file	*get_buffer(t_file **head, int fd, t_bool destroy)
{
	t_file	*next;

	while (*head && (*head)->fd != fd)
		head = &(*head)->next;
	if (!*head)
	{
		if (!(*head = (t_file *)ft_memalloc(sizeof(t_file))))
			return (NULL);
		if (!((*head)->buffer = ft_memalloc(BUFF_SIZE + 1)))
		{
			ft_memdel((void **)head);
			return (NULL);
		}
		(*head)->fd = fd;
	}
	if (destroy)
	{
		next = (*head)->next;
		free((*head)->buffer);
		free(*head);
		*head = next;
	}
	return (*head);
}

static t_bool	append(char **line, char *buffer, size_t n)
{
	char	*tmp;
	size_t	len;

	if (!*line)
	{
		if (!(*line = ft_strsub(buffer, 0, n)))
			return (FALSE);
	}
	else
	{
		tmp = *line;
		len = ft_strlen(tmp) + n;
		if (!(*line = (char *)malloc(len + 1)))
			return (FALSE);
		ft_memcpy(ft_stpcpy(*line, tmp), buffer, n);
		(*line)[len] = '\0';
		free(tmp);
	}
	return (TRUE);
}

static int		build_line(t_file **head, char **line, t_file *file)
{
	char	*buffer;
	size_t	n;

	if (!*(buffer = file->buffer + file->offset))
		return (0);
	n = 0;
	while (buffer[n] && buffer[n] != '\n')
		++n;
	if (!append(line, buffer, n))
	{
		get_buffer(head, file->fd, TRUE);
		if (*line)
			ft_memdel((void **)line);
		return (-1);
	}
	if (buffer[n] == '\n')
	{
		file->offset += n + 1;
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*head;
	t_file			*file;
	ssize_t			bytes;
	int				nl;

	if (!line || !(file = get_buffer(&head, fd, FALSE)))
		return (-1);
	*line = NULL;
	while (!(nl = build_line(&head, line, file)))
	{
		if ((bytes = read(fd, file->buffer, BUFF_SIZE)) < 1)
		{
			get_buffer(&head, fd, TRUE);
			if (*line && bytes < 0)
				ft_memdel((void **)line);
			return ((*line) ? 1 : bytes);
		}
		file->buffer[bytes] = '\0';
		file->offset = 0;
	}
	return (nl);
}
