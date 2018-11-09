/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 22:03:27 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/09 07:17:59 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Pulls 2-byte address from relative address provided in argument for indirect
**  values.
*/

t_bool	op_sti(t_core *core, t_proc *p, t_instr *instr)
{
	t_byte	*src;
	int32_t	off;

	if (instr->atypes[1] & T_I)
	{
		off = read_core(core, instr->args[1], IND_SIZE, FALSE);
		src = IDX_POS(core->arena, p->pc, off);
		off = read_core(core, src, DIR_SIZE, FALSE);
	}
	else
		off = read_arg(core, p, 1);
	off += read_arg(core, p, 2);
	write_core(core, IDX_POS(core->arena, p->pc, off), p, 0);
	return (p->carry);
}
