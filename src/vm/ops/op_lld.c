/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 23:32:25 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/04 16:28:18 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_lld(t_core *core, t_proc *p, t_instr *instr)
{
	t_byte	*src;
	int32_t	*dst;
	int32_t	off;

	dst = (int32_t *)instr->args[1];
	if (instr->atypes[0] & T_D)
		*dst = read_arg(core, p, 0);
	else
	{
		off = read_core(core, instr->args[0], IND_SIZE, FALSE);
		src = ABS_POS(core->arena, p->pc, off);
		*dst = read_core(core, src, IND_SIZE, FALSE);
	}
	return (!*dst);
}
