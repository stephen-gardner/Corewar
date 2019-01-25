/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 22:19:37 by sgardner          #+#    #+#             */
/*   Updated: 2019/01/25 00:56:08 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Argument is a 2 byte relative address % IDX_MOD.
**
** WARNING: Forking may cause the parent process to shift to a new memory
**  address.
*/

t_bool	op_fork(t_core *core, t_proc *p, t_instr *instr)
{
	t_byte	*fpc;
	int32_t	off;

	off = read_core(core, instr->epc, IND_SIZE, FALSE);
	fpc = IDX_POS(core->arena, p->pc, off);
	p->pc = ABS_POS(core->arena, instr->epc, IND_SIZE);
	instr->op = NOP;
	fork_process(core, p, fpc);
	return (0);
}
