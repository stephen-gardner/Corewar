/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 04:32:22 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/24 06:14:31 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

const char		*g_errmsg[6] = {
	"%s",
	"%s: %s",
	"%s: exceeds max champion size (%u > %u)",
	"%s: too small to be a champion",
	"%s: invalid header",
	"%s: code size does not match size specified in header"
};

static void		build_out(char *out, t_byte *arena, int addrlen)
{
	size_t	line;
	size_t	i;

	i = 0;
	line = 0;
	out += ft_sprintf(out, "0x%.*x: ", addrlen, 0);
	while (i < MEM_SIZE)
	{
		if (++line == DUMP_LEN)
		{
			line = 0;
			out += ft_sprintf(out, "%.2x\n", arena[i++]);
			if (i < MEM_SIZE)
				out += ft_sprintf(out, "%#.*x: ", addrlen, i);
			continue ;
		}
		out += ft_sprintf(out, "%.2x ", arena[i++]);
	}
}

static size_t	calc_olen(int *addrlen, size_t msize)
{
	int		alen;

	alen = 0;
	if (!msize)
		alen = 1;
	while (msize)
	{
		++alen;
		msize /= 16;
	}
	*addrlen = alen;
	return (((MEM_SIZE / DUMP_LEN) * (alen + 4)) + (MEM_SIZE * 3));
}

/*
** Prints the arena to stdout in hexadecimal, with DUMP_LEN bytes per line.
*/

void			dump(t_core *core)
{
	char	*out;
	size_t	olen;
	int		addrlen;

	olen = calc_olen(&addrlen, MEM_SIZE);
	if (!(out = malloc(olen + 1)))
		SYS_ERR;
	build_out(out, core->arena, addrlen);
	write(STDOUT_FILENO, out, olen);
	free(out);
}

/*
** Prints error message from g_errmsg with given id to stderr and exits the
**  program.
*/

void			error(int id, ...)
{
	char	*msg;
	va_list	ap;

	va_start(ap, id);
	if (vasprintf(&msg, g_errmsg[id], ap))
	{
		ft_dprintf(STDERR_FILENO, "%&s %s\n", "31m", "Error:", msg);
		free(msg);
	}
	va_end(ap);
	exit(EXIT_FAILURE);
}
