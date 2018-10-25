/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 21:02:58 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/25 10:19:39 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

const t_op	g_ops[17] = {
	{"live", 10, 0x01, 1, {T_D}, 0, 0},
	{"ld", 5, 0x02, 2, {T_D | T_I, T_R}, 1, 0},
	{"st", 5, 0x03, 2, {T_R, T_I | T_R}, 1, 0},
	{"add", 10, 0x04, 3, {T_R, T_R, T_R}, 1, 0},
	{"sub", 10, 0x05, 3, {T_R, T_R, T_R}, 1, 0},
	{"and", 6, 0x06, 3, {T_R | T_D | T_I, T_R | T_I | T_D, T_R}, 1, 0},
	{"or", 6, 0x07, 3, {T_R | T_I | T_D, T_R | T_I | T_D, T_R}, 1, 0},
	{"xor", 6, 0x08, 3, {T_R | T_I | T_D, T_R | T_I | T_D, T_R}, 1, 0},
	{"zjmp", 20, 0x09, 1, {T_D}, 0, 1},
	{"ldi", 25, 0x0A, 3, {T_R | T_D | T_I, T_D | T_R, T_R}, 1, 1},
	{"sti", 25, 0x0B, 3, {T_R, T_R | T_D | T_I, T_D | T_R}, 1, 1},
	{"fork", 800, 0x0C, 1, {T_D}, 0, 1},
	{"lld", 10, 0x0D, 2, {T_D | T_I, T_R}, 1, 0},
	{"lldi", 50, 0x0E, 3, {T_R | T_D | T_I, T_D | T_R, T_R}, 1, 1},
	{"lfork", 1000, 0x0F, 1, {T_D}, 0, 1},
	{"aff", 2, 0x10, 1, {T_R}, 1, 0},
	{"undefined", 0, 0x00, 0, {0}, 0, 0}
};

static t_bool	set_register(t_byte *arena, t_byte **pos, t_proc *p, int i)
{
	t_byte	n;

	n = **pos;
	if (n > REG_NUMBER)
		return (FALSE);
	p->target.params[i] = (t_byte *)&p->registers[n - 1];
	*pos = ABS_POS(arena, *pos, 1);
	return (TRUE);
}

static t_bool	set_params(t_byte *arena, t_proc *p)
{
	t_byte	*pos;
	int		i;

	i = 0;
	pos = ABS_POS(arena, p->pc, 2);
	while (i < p->op->nparams)
	{
		if (!(p->target.types[i] & p->op->ptypes[i]))
			return (FALSE);
		if ((p->target.types[i] & T_R) && !set_register(arena, &pos, p, i))
			return (FALSE);
		else
		{
			p->target.params[i] = pos;
			if (p->target.types[i] & T_D)
				pos = ABS_POS(arena, pos, DIR_SIZE);
			else
				pos = ABS_POS(arena, pos, IND_SIZE);
		}
		++i;
	}
	p->target.end = pos;
	return (TRUE);
}

t_bool			decode(t_byte *arena, t_proc *p)
{
	t_byte	acb;
	t_byte	type;
	int		i;

	i = 0;
	acb = *ABS_POS(arena, p->pc, 1);
	while (i < p->op->nparams)
	{
		type = acb & 0xC0;
		if (type == 0x40)
			p->target.types[i] = T_R;
		else if (type == 0x80)
			p->target.types[i] = T_D;
		else
			p->target.types[i] = T_I;
		acb <<= 2;
		++i;
	}
	while (i++ < 5)
	{
		if (acb & 0xC0)
			return (FALSE);
		acb <<= 2;
	}
	return (set_params(arena, p));
}
