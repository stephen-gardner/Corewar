/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 00:04:06 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/03 17:46:23 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_lfork(t_core *core, t_proc *p, t_instr *instr)
{
	t_uint	off;

	off = read_core(core, instr->epc, IND_SIZE, FALSE);
	instr->epc = ABS_POS(core->arena, instr->epc, IND_SIZE);
	fork_process(core, p, ABS_POS(core->arena, p->pc, off));
	return (p->carry);
}
