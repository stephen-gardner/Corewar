/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 17:29:57 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/01 23:12:55 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
