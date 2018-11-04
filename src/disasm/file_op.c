/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 17:29:57 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/10 14:07:25 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

#include <stdlib.h>

void	quit(int errnum, void *memory)
{
	if (memory != NULL)
		free(memory);
	ft_printf("%s\n", strerror(errnum));
	exit(EXIT_FAILURE);
}

ssize_t	getfilesize(char *filename)
{
	int		fd;
	ssize_t	size;
	int		r;
	char	buf;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	size = 0;
	while ((r = read(fd, &buf, 1)) == 1)
		size++;
	close(fd);
	if (r == 0)
		return (size);
	else
		return (-1);
}

void	*getfilecontents(char *filename, size_t *size)
{
	ssize_t			r;
	int				fd;
	unsigned char	*mem;

	if (filename == NULL)
		return (stdin_read_eof(size));
	if ((int)(*size = getfilesize(filename)) == -1)
		quit(errno, NULL);
	if ((mem = ft_memalloc(*size + 1)) == NULL)
		quit(errno, NULL);
	if ((fd = open(filename, O_RDONLY)))
	{
		r = read(fd, mem, *size);
		close(fd);
		if (r == (ssize_t)*size)
			return (mem);
	}
	free(mem);
	quit(errno, NULL);
	return (NULL);
}

int		put_file_contents(char *filename, unsigned char *data, size_t size)
{
	int		fd;

	if ((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		return (0);
	if ((write(fd, data, size)) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
