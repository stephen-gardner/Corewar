/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 20:56:43 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/10 14:07:39 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

#include <stdlib.h>

void	stdin_quit(char *membuf)
{
	if (membuf != NULL)
		free(membuf);
	ft_printf("%s\n", strerror(errno));
	exit(0);
}

char	*stdin_read_eof(size_t *count)
{
	char	*buffer;
	char	*newbuf;
	ssize_t	r;

	if ((buffer = ft_memalloc(1024)) == NULL)
		stdin_quit(NULL);
	r = 1;
	while (r != 0)
	{
		if ((r = read(0, &buffer[*count], 1024 - (*count % 1024))) == -1)
			stdin_quit(buffer);
		*count += r;
		if ((*count) && (*count % 1024 == 0) && (r != 0))
		{
			if ((newbuf = ft_memalloc(*count + 1024)) == NULL)
				stdin_quit(buffer);
			memcpy(newbuf, buffer, *count);
			free(buffer);
			buffer = newbuf;
			r = 1;
		}
	}
	return (buffer);
}
