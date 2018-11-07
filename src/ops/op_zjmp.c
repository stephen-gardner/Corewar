/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 20:24:30 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/07 05:25:43 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Process PC is set to 2-byte relative address if carry flag is TRUE.
*/

t_bool	op_zjmp(t_core *core, t_proc *p, t_instr *instr)
{
	int32_t	off;

	if (p->carry)
	{
		off = read_core(core, instr->epc, IND_SIZE, FALSE);
		instr->epc = IDX_POS(core->arena, p->pc, off);
	}
	else
		instr->epc = ABS_POS(core->arena, instr->epc, IND_SIZE);
	return (p->carry);
}
