/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coreio.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 01:09:10 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/03 23:37:24 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	age_arena(t_byte *epoch)
{
	size_t	i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (epoch[i] < 254)
			++epoch[i];
	}
}

t_uint	read_arg(t_core *core, t_proc *p, int a)
{
	t_instr	*instr;
	t_byte	*src;
	t_uint	off;

	instr = &p->instr;
	if (instr->atypes[a] & T_R)
		return (*((t_uint *)instr->args[a]));
	if (instr->atypes[a] & T_I)
	{
		off = read_core(core, instr->args[a], IND_SIZE, FALSE);
		src = IDX_POS(core->arena, p->pc, off);
		return (read_core(core, src, DIR_SIZE, instr->op->trunc));
	}
	return (read_core(core, instr->args[a], DIR_SIZE, instr->op->trunc));
}

t_uint	read_core(t_core *core, t_byte *src, int n, t_bool trunc)
{
	t_byte	*dst;
	t_uint	res;
	int		i;

	i = -1;
	res = 0;
	dst = (t_byte *)&res;
	while (++i < n)
		dst[(n - 1) - i] = *ABS_POS(core->arena, src, i);
	if (trunc)
		res >>= ((DIR_SIZE - IND_SIZE) << 3);
	return (res);
}

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
		core->owner[off] = (p->champ - core->champions) + 1;
		core->epoch[off] = 0;
	}
}
