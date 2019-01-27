/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 00:04:06 by sgardner          #+#    #+#             */
/*   Updated: 2019/01/27 06:14:55 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Argument is a 2-byte relative address.
**
** WARNING: Forking may cause the parent process to shift to a new memory
**  address.
*/

t_bool	op_lfork(t_core *core, t_proc *p, t_instr *instr)
{
	t_byte	*fpc;
	int32_t	off;

	off = read_core(core, instr->epc, IND_SIZE, FALSE);
	fpc = ABS_POS(core->arena, p->pc, off);
	instr->op = NOP;
	set_pc(core, p, ABS_POS(core->arena, instr->epc, IND_SIZE),
		p - core->procpool.procs);
	fork_process(core, p, fpc);
	return (0);
}
