/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 04:32:22 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/01 07:59:44 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

const char		*g_errmsg[NERRMSGS] = {
	"%s",
	"%s: %s",
	"%s: exceeds max champion size (%u > %u)",
	"%s: too small to be a champion",
	"%s: invalid header",
	"%s: code size does not match size specified in header",
	"too many champions specified"
};

const char		*g_notices[NNOTICES] = {
	"Cycle %u: Player %u (%s) wins!",
	"A process shows that player %u (%s) is alive",
	"Cycle %u: All players have died without ever really living...",
	"Launching GUI..."
};

static void		build_dump(char *out, t_byte *arena, int addrlen)
{
	size_t	line;
	size_t	i;

	i = 0;
	line = 0;
	out += ft_sprintf(out, "0x%.*x : ", addrlen, 0);
	while (i < MEM_SIZE)
	{
		out += ft_sprintf(out, "%.2x ", arena[i++]);
		if (++line == DUMP_LEN)
		{
			line = 0;
			out += ft_sprintf(out, "\n", arena[i++]);
			if (i < MEM_SIZE)
				out += ft_sprintf(out, "%#.*x : ", addrlen, i);
			continue ;
		}
	}
}

static size_t	dumplen(int *addrlen)
{
	int	msize;
	int	alen;

	alen = 0;
	if (!(msize = MEM_SIZE))
		alen = 1;
	while (msize)
	{
		++alen;
		msize /= 16;
	}
	*addrlen = alen;
	return (((MEM_SIZE / DUMP_LEN) * (alen + 6)) + (MEM_SIZE * 3));
}

/*
** Prints the arena to stdout in hexadecimal, with DUMP_LEN bytes per line.
*/

void			dump(t_core *core)
{
	char	*out;
	size_t	olen;
	char	*sep;
	int		slen;
	int		addrlen;

	olen = dumplen(&addrlen);
	slen = (DUMP_LEN * 3) + addrlen + 4;
	if (!(out = malloc(olen + 1)))
		SYS_ERR;
	if (!(sep = malloc(slen + 1)))
		SYS_ERR;
	sep[slen] = '\0';
	ft_memset(sep, '-', slen);
	build_dump(out, core->arena, addrlen);
	ft_printf("%s\nCORE DUMP [CYCLE %u]\n%s\n", sep, --core->cycle, sep);
	write(STDOUT_FILENO, out, olen);
	free(out);
	free(sep);
	exit(EXIT_SUCCESS);
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
	if (ft_vasprintf(&msg, g_errmsg[id], ap))
	{
		ft_dprintf(STDERR_FILENO, "%&s %s\n", "31m", "Error:", msg);
		free(msg);
	}
	va_end(ap);
	exit(EXIT_FAILURE);
}

void			notice(int id, ...)
{
	va_list	ap;

	va_start(ap, id);
	ft_vprintf(g_notices[id], ap);
	va_end(ap);
	write(STDOUT_FILENO, "\n", 1);
}
