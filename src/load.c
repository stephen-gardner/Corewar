/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 02:28:56 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/05 07:20:11 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

#define IO_ERR(path)	ERR(BAD_IO, path, strerror(errno))

t_champ		*find_champ(t_core *core, int32_t id)
{
	int	i;

	i = 0;
	while (i < core->nplayers && core->champions[i].id != id)
		++i;
	return ((i < core->nplayers) ? &core->champions[i] : NULL);
}

/*
** Checks if file size is too small, if magic is invalid, if code size doesn't
**  match size specified in header, and if code size is too large.
*/

static void	load_header(int fd, const char *path, t_header *header)
{
	off_t	size;

	if ((size = lseek(fd, 0, SEEK_END)) == -1)
		IO_ERR(path);
	if ((size_t)size < sizeof(t_header))
		ERR(CHAMP_TOO_SMALL, path);
	if (lseek(fd, 0, SEEK_SET) == -1)
		IO_ERR(path);
	if (read(fd, header, sizeof(t_header)) != sizeof(t_header))
		IO_ERR(path);
	REV(&header->magic, sizeof(header->magic));
	if (header->magic != COREWAR_EXEC_MAGIC)
		ERR(INVALID_HEADER, path);
	REV(&header->prog_size, sizeof(header->prog_size));
	if (header->prog_size != size - sizeof(t_header))
		ERR(SIZE_MISMATCH, path);
	if (header->prog_size > CHAMP_MAX_SIZE)
		ERR(CHAMP_TOO_LARGE, path, header->prog_size, CHAMP_MAX_SIZE);
}

void		load_champ(t_core *core, const char *path, int pnum)
{
	t_proc		*p;
	t_byte		*pc;
	t_champ		*champ;
	t_header	header;
	int			fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		IO_ERR(path);
	load_header(fd, path, &header);
	champ = &core->champions[pnum];
	ft_memcpy(champ->name, header.prog_name, PROG_NAME_LENGTH);
	ft_memcpy(champ->comment, header.comment, COMMENT_LENGTH);
	pc = &core->arena[(MEM_SIZE / core->nplayers) * pnum];
	if (read(fd, pc, header.prog_size) != header.prog_size)
		IO_ERR(path);
	p = fork_process(core, NULL, pc);
	p->champ = find_champ(core, champ->id);
	p->registers[0] = p->champ->id;
	if (core->gui)
	{
		ft_memset(core->owner + (pc - core->arena),
			(p->champ - core->champions) + 1, header.prog_size);
	}
	close(fd);
}
