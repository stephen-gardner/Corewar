/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 21:02:58 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/27 21:10:28 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

const t_op		g_ops[17] = {
	{"live", op_live, 10, 0x01, 1, {T_D}, 0, 0},
	{"ld", op_ld, 5, 0x02, 2, {T_D | T_I, T_R}, 1, 0},
	{"st", op_st, 5, 0x03, 2, {T_R, T_R | T_I}, 1, 0},
	{"add", op_add, 10, 0x04, 3, {T_R, T_R, T_R}, 1, 0},
	{"sub", op_sub, 10, 0x05, 3, {T_R, T_R, T_R}, 1, 0},
	{"and", op_and, 6, 0x06, 3, {T_R | T_I | T_D, T_R | T_I | T_D, T_R}, 1, 0},
	{"or", op_or, 6, 0x07, 3, {T_R | T_I | T_D, T_R | T_I | T_D, T_R}, 1, 0},
	{"xor", op_xor, 6, 0x08, 3, {T_R | T_I | T_D, T_R | T_I | T_D, T_R}, 1, 0},
	{"zjmp", op_zjmp, 20, 0x09, 1, {T_D}, 0, 1},
	{"ldi", op_nop, 25, 0x0A, 3, {T_R | T_I | T_D, T_R | T_D, T_R}, 1, 1},
	{"sti", op_nop, 25, 0x0B, 3, {T_R, T_R | T_I | T_D, T_R | T_D}, 1, 1},
	{"fork", op_nop, 800, 0x0C, 1, {T_D}, 0, 1},
	{"lld", op_nop, 10, 0x0D, 2, {T_I | T_D, T_R}, 1, 0},
	{"lldi", op_nop, 50, 0x0E, 3, {T_R | T_I | T_D, T_R | T_D, T_R}, 1, 1},
	{"lfork", op_nop, 1000, 0x0F, 1, {T_D}, 0, 1},
	{"aff", op_nop, 2, 0x10, 1, {T_R}, 1, 0},
	{"undefined", op_nop, 0, 0x00, 0, {0}, 0, 0}
};

const t_uint	g_ops_size = sizeof(g_ops) / sizeof(t_op);

static t_bool	set_param(t_byte *arena, t_proc *p, t_byte **pos, int i)
{
	t_instr	*instr;

	instr = &p->instr;
	if (!(instr->atypes[i] & OP(p)->ptypes[i]))
		return (FALSE);
	if (instr->atypes[i] & T_R)
	{
		if (**pos > REG_NUMBER)
			return (FALSE);
		instr->args[i] = (t_byte *)&p->registers[**pos - 1];
		*pos = ABS_POS(arena, *pos, 1);
		return (TRUE);
	}
	instr->args[i] = *pos;
	if ((instr->atypes[i] & T_D) && !OP(p)->trunc)
		*pos = ABS_POS(arena, *pos, DIR_SIZE);
	else
		*pos = ABS_POS(arena, *pos, IND_SIZE);
	return (TRUE);
}

t_bool			decode(t_byte *arena, t_proc *p)
{
	t_byte	*pos;
	t_byte	acb;
	int		i;

	pos = p->instr.epc;
	acb = *pos;
	i = 0;
	while (i < OP(p)->nparams)
	{
		if ((acb & 0xC0) == 0x40)
			p->instr.atypes[i] = T_R;
		else if ((acb & 0xC) == 0x80)
			p->instr.atypes[i] = T_D;
		else
			p->instr.atypes[i] = T_I;
		if (!set_param(arena, p, &pos, i))
			return (FALSE);
		acb <<= 2;
		++i;
	}
	if (acb)
		return (FALSE);
	p->instr.epc = pos;
	return (TRUE);
}

t_bool			op_nop(t_core *core, t_proc *p)
{
	UNUSED(core);
	UNUSED(p);
	return (p->carry);
}
