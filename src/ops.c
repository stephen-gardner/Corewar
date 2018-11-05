/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 21:02:58 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/05 07:04:18 by sgardner         ###   ########.fr       */
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
	{"nop", op_nop, 1, 0x00, 0, {0}, 0, 0}
};

const t_uint	g_ops_size = sizeof(g_ops) / sizeof(t_op);

static t_bool	set_param(t_byte *arena, t_proc *p, t_instr *instr, int i)
{
	t_bool	res;

	res = TRUE;
	if (!(instr->atypes[i] & instr->op->ptypes[i]))
		res = FALSE;
	if (instr->atypes[i] & T_R)
	{
		if ((t_byte)(*instr->epc - 1) >= REG_NUMBER)
			res = FALSE;
		else
			instr->args[i] = (t_byte *)&p->registers[*instr->epc - 1];
		instr->epc = ABS_POS(arena, instr->epc, 1);
		return (res);
	}
	instr->args[i] = instr->epc;
	if ((instr->atypes[i] & T_D) && !instr->op->trunc)
		instr->epc = ABS_POS(arena, instr->epc, DIR_SIZE);
	else
		instr->epc = ABS_POS(arena, instr->epc, IND_SIZE);
	return (res);
}

t_bool			decode(t_byte *arena, t_proc *p, t_instr *instr)
{
	t_bool	res;
	t_byte	acb;
	int		i;

	res = TRUE;
	acb = *instr->epc;
	instr->epc = ABS_POS(arena, instr->epc, 1);
	i = -1;
	while (++i < instr->op->nparams)
	{
		if (!(acb & 0xC0))
			res = FALSE;
		else if ((acb & 0xC0) == 0x40)
			p->instr.atypes[i] = T_R;
		else if ((acb & 0xC0) == 0x80)
			p->instr.atypes[i] = T_D;
		else
			p->instr.atypes[i] = T_I;
		if ((acb & 0xC0) && !set_param(arena, p, instr, i))
			res = FALSE;
		acb <<= 2;
	}
	return (res);
}
