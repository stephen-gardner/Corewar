/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 22:19:37 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/29 21:32:33 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_fork(t_core *core, t_proc *p)
{
	t_instr	*instr;
	t_byte	*fpc;

	instr = &p->instr;
	instr->args[0] = instr->epc;
	instr->atypes[0] = instr->op->ptypes[0];
	fpc = IDX_POS(core->arena, p->pc, read_data(core, instr, 0));
	instr->epc = ABS_POS(core->arena, instr->epc, IND_SIZE);
	fork_process(core, p, fpc);
	return (p->carry);
}
