/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 00:04:06 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/06 23:54:54 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Argument is a 2-byte relative address.
*/

t_bool	op_lfork(t_core *core, t_proc *p, t_instr *instr)
{
	int32_t	off;

	off = read_core(core, instr->epc, IND_SIZE, FALSE);
	instr->epc = ABS_POS(core->arena, instr->epc, IND_SIZE);
	fork_process(core, p, ABS_POS(core->arena, p->pc, off));
	return (p->carry);
}
