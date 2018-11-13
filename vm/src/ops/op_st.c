/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 07:45:38 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/09 07:17:41 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Writes value from a register to another register, or a 2-byte relative
**  address.
*/

t_bool	op_st(t_core *core, t_proc *p, t_instr *instr)
{
	int32_t	val;
	int32_t	off;

	val = read_arg(core, p, 0);
	if (instr->atypes[1] & T_R)
		*((int32_t *)instr->args[1]) = val;
	else
	{
		off = read_core(core, instr->args[1], IND_SIZE, FALSE);
		instr->args[2] = (t_byte *)&val;
		instr->atypes[2] = T_R;
		write_core(core, IDX_POS(core->arena, p->pc, off), p, 2);
	}
	return (p->carry);
}
