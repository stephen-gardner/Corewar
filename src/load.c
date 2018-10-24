/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 02:28:56 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/23 20:04:33 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ft_printf.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

# define SYS_ERR(path)	ERR(BAD_IO, path, strerror(errno))

static t_bool	load_header(t_header *header, const char *path, int fd)
{
	off_t	size;

	if ((size = lseek(fd, 0, SEEK_END)) == -1)
		return (SYS_ERR(path));
	if ((size_t)size < sizeof(t_header))
		return (ERR(CHAMP_TOO_SMALL, path));
	if (lseek(fd, 0, SEEK_SET) == -1)
		return (SYS_ERR(path));
	if (read(fd, header, sizeof(t_header)) != sizeof(t_header))
		return (SYS_ERR(path));
	REV(&header->magic, sizeof(header->magic));
	if (header->magic != COREWAR_EXEC_MAGIC)
		return (ERR(INVALID_HEADER, path));
	REV(&header->prog_size, sizeof(header->prog_size));
	if (header->prog_size != size - sizeof(t_header))
		return (ERR(SIZE_MISMATCH, path));
	if (header->prog_size > CHAMP_MAX_SIZE)
		return (ERR(CHAMP_TOO_LARGE, path, header->prog_size, CHAMP_MAX_SIZE));
	return (TRUE);
}

static t_bool	load_code(t_core *core, t_header *header, const char *path,
					int fd)
{
	t_champ	*champ;
	t_byte	*pos;

	champ = &core->champions[core->cycle];
	ft_memcpy(champ->name, header->prog_name, PROG_NAME_LENGTH);
	ft_memcpy(champ->comment, header->comment, COMMENT_LENGTH);
	pos = &core->arena[(MEM_SIZE / core->nplayers) * core->cycle];
	if (read(fd, pos, header->prog_size) != header->prog_size)
	{
		close(fd);
		return (SYS_ERR(path));
	}
	close(fd);
	++core->cycle;
	return (TRUE);
}

t_bool			load_champ(t_core *core, const char *path)
{
	t_header	header;
	int			fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (SYS_ERR(path));
	return (load_header(&header, path, fd)
		&& load_code(core, &header, path, fd));
}
