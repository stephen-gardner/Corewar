/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 02:28:56 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/23 07:09:26 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

static t_bool	load_header(t_header *header, const char *path, int fd,
					size_t size)
{
	if (lseek(fd, 0, SEEK_SET) == -1
		|| read(fd, header, sizeof(t_header)) != sizeof(t_header))
	{
		close(fd);
		return (error("cannot read %s", path));
	}
	ft_revbytes(&header->magic, sizeof(header->magic));
	if (header->magic != COREWAR_EXEC_MAGIC)
	{
		close(fd);
		return (error("invalid header for %s", path));
	}
	ft_revbytes(&header->prog_size, sizeof(header->prog_size));
	if (header->prog_size != size - sizeof(t_header))
	{
		close(fd);
		return (error("code size does not match size in header for %s", path));
	}
	if (header->prog_size > CHAMP_MAX_SIZE)
	{
		close(fd);
		return (error("%s exceeds max champion size (%zu > %zu)", path,
			(size_t)header->prog_size, (size_t)CHAMP_MAX_SIZE));
	}
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
		return (error("cannot read %s", path));
	}
	close(fd);
	++core->cycle;
	return (TRUE);
}

t_bool			load_champ(t_core *core, const char *path)
{
	t_header	header;
	int			fd;
	off_t		size;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (error("unable to open %s", path));
	if ((size = lseek(fd, 0, SEEK_END)) == -1)
	{
		close(fd);
		return (error("cannot read %s", path));
	}
	if ((size_t)size < sizeof(t_header))
	{
		close(fd);
		return (error("%s is too small to be a champion\n", path));
	}
	return (load_header(&header, path, fd, (size_t)size)
		&& load_code(core, &header, path, fd));
}
