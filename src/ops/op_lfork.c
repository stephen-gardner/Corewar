/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 00:04:06 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/29 04:41:05 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_lfork(t_core *core, t_proc *p)
{
	t_instr	*instr;
	t_proc	*clone;

	instr = &p->instr;
	clone = fork_process(core, p);
	instr->args[0] = instr->epc;
	instr->atypes[0] = instr->op->ptypes[0];
	clone->pc = ABS_POS(core->arena, p->pc, read_data(core, instr, 0));
	instr->epc = ABS_POS(core->arena, instr->epc, IND_SIZE);
	return (p->carry);
}
