/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 22:19:37 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/29 04:40:11 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_fork(t_core *core, t_proc *p)
{
	t_instr	*instr;
	t_proc	*clone;

	instr = &p->instr;
	clone = fork_process(core, p);
	instr->args[0] = instr->epc;
	instr->atypes[0] = instr->op->ptypes[0];
	clone->pc = IDX_POS(core->arena, p->pc, read_data(core, instr, 0));
	instr->epc = ABS_POS(core->arena, instr->epc, IND_SIZE);
	return (p->carry);
}
