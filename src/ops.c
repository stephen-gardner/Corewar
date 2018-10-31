/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 21:02:58 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/30 22:30:03 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

const t_op		g_ops[17] = {
	{"live", op_live, 10, 0x01, 1, {T_D}, 0, 0},
	{"ld", op_ld, 5, 0x02, 2, {T_I | T_D, T_R}, 1, 0},
	{"st", op_st, 5, 0x03, 2, {T_R, T_R | T_I}, 1, 0},
	{"add", op_add, 10, 0x04, 3, {T_R, T_R, T_R}, 1, 0},
	{"sub", op_sub, 10, 0x05, 3, {T_R, T_R, T_R}, 1, 0},
	{"and", op_and, 6, 0x06, 3, {T_R | T_I | T_D, T_R | T_I | T_D, T_R}, 1, 0},
	{"or", op_or, 6, 0x07, 3, {T_R | T_I | T_D, T_R | T_I | T_D, T_R}, 1, 0},
	{"xor", op_xor, 6, 0x08, 3, {T_R | T_I | T_D, T_R | T_I | T_D, T_R}, 1, 0},
	{"zjmp", op_zjmp, 20, 0x09, 1, {T_D}, 0, 1},
	{"ldi", op_ldi, 25, 0x0A, 3, {T_R | T_I | T_D, T_R | T_D, T_R}, 1, 1},
	{"sti", op_sti, 25, 0x0B, 3, {T_R, T_R | T_I | T_D, T_R | T_D}, 1, 1},
	{"fork", op_fork, 800, 0x0C, 1, {T_D}, 0, 1},
	{"lld", op_lld, 10, 0x0D, 2, {T_I | T_D, T_R}, 1, 0},
	{"lldi", op_lldi, 50, 0x0E, 3, {T_R | T_I | T_D, T_R | T_D, T_R}, 1, 1},
	{"lfork", op_lfork, 1000, 0x0F, 1, {T_D}, 0, 1},
	{"aff", op_aff, 2, 0x10, 1, {T_R}, 1, 0},
	{"undefined", op_nop, 1, 0x00, 0, {0}, 0, 0}
};

const t_uint	g_ops_size = sizeof(g_ops) / sizeof(t_op);

static t_bool	invalid_acb(t_byte *arena, t_proc *p)
{
	t_instr	*instr;
	t_byte	acb;
	int		i;

	i = 0;
	instr = &p->instr;
	acb = *instr->epc;
	instr->epc = ABS_POS(arena, instr->epc, 1);
	while (acb && i < instr->op->nparams)
	{
		if ((acb & 0xC0) == 0x40)
			instr->epc = ABS_POS(arena, instr->epc, T_R);
		else if ((acb & 0xC0) == 0x80)
		{
			if (instr->op->trunc)
				instr->epc = ABS_POS(arena, instr->epc, T_I);
			else
				instr->epc = ABS_POS(arena, instr->epc, T_D);
		}
		else if ((acb & 0xC0) == 0xC0)
			instr->epc = ABS_POS(arena, instr->epc, T_I);
		acb <<= 2;
		++i;
	}
	return (FALSE);
}

static t_bool	set_param(t_byte *arena, t_proc *p, t_byte **pos, int i)
{
	t_instr	*instr;

	instr = &p->instr;
	if (!(instr->atypes[i] & instr->op->ptypes[i]))
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
	if ((instr->atypes[i] & T_D) && !instr->op->trunc)
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

	acb = *p->instr.epc;
	pos = ABS_POS(arena, p->instr.epc, 1);
	i = -1;
	while (++i < OP(p)->nparams)
	{
		if (!(acb & 0xC0))
			return (invalid_acb(arena, p));
		else if ((acb & 0xC0) == 0x40)
			p->instr.atypes[i] = T_R;
		else if ((acb & 0xC0) == 0x80)
			p->instr.atypes[i] = T_D;
		else
			p->instr.atypes[i] = T_I;
		if (!set_param(arena, p, &pos, i))
			return (invalid_acb(arena, p));
		acb <<= 2;
	}
	if (acb)
		return (invalid_acb(arena, p));
	p->instr.epc = pos;
	return (TRUE);
}

t_bool			op_nop(t_core *core, t_proc *p)
{
	UNUSED(core);
	UNUSED(p);
	return (p->carry);
}
