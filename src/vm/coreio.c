/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coreio.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 01:09:10 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/07 18:53:00 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "corewar_gui.h"

/*
** GUI - Increments all unmaxed age data by 1.
*/

void	age_arena(t_byte *epoch)
{
	size_t	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (epoch[i] < LUM_MAX_STEPS)
			epoch[i]++;
		i++;
	}
}

/*
** Reads the argument for given index to a 32-bit signed integer and returns it.
** Register values are read from the register with no processing.
** Direct values are read from the core at the address provided.
** Indirect addresses are 2 bytes read from the core at the address provided,
**  and that address is used to read the 4 byte (2 bytes if its an op that
**  specifies truncation) return value from the core.
*/

int32_t	read_arg(t_core *core, t_proc *p, int a)
{
	t_instr	*instr;
	t_byte	*src;
	int32_t	off;

	instr = &p->instr;
	if (instr->atypes[a] & T_R)
		return (*((int32_t *)instr->args[a]));
	if (instr->atypes[a] & T_I)
	{
		off = read_core(core, instr->args[a], IND_SIZE, FALSE);
		src = IDX_POS(core->arena, p->pc, off);
		return (read_core(core, src, DIR_SIZE, instr->op->trunc));
	}
	return (read_core(core, instr->args[a], DIR_SIZE, instr->op->trunc));
}

/*
** Reads data from the core. The core is in big endian, so the bytes must be
**  read backwards. At this time, it is assumed that this code will be compiled
**  on a little endian machine.
** If truncation is specified, the data is shifted into a 2 byte value.
** The return data is casted to a signed type of the appropriate size to ensure
**  that the sign is preserved in the 4 byte register.
*/

int32_t	read_core(t_core *core, t_byte *src, int n, t_bool trunc)
{
	t_byte		*dst;
	uint32_t	res;
	int			i;

	i = -1;
	res = 0;
	dst = (t_byte *)&res;
	while (++i < n)
		dst[(n - 1) - i] = *ABS_POS(core->arena, src, i);
	if (trunc)
		res >>= ((DIR_SIZE - IND_SIZE) << 3);
	if (n == IND_SIZE || trunc)
		res = (int16_t)res;
	return ((int32_t)res);
}

/*
** Writes data from instruction argument of given index (a) to the core.
** The data is assumed to be in little endian, and written to the core in
**  reverse.
** If the GUI is enabled, the byte ownership is also set, and its age reset.
*/

void	write_core(t_core *core, t_byte *dst, t_proc *p, int a)
{
	t_instr	*instr;
	t_uint	off;
	int		n;
	int		i;

	instr = &p->instr;
	n = (instr->atypes[a] & T_I) ? IND_SIZE : REG_SIZE;
	i = -1;
	while (++i < n)
	{
		off = ABS_POS(core->arena, dst, ((n - 1) - i)) - core->arena;
		core->arena[off] = instr->args[a][i];
		if (core->gui)
		{
			core->owner[off] = (p->champ - core->champions) + 1;
			core->epoch[off] = 0;
		}
	}
}
