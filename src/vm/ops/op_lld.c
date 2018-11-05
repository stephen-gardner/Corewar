/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 23:32:25 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/31 08:59:52 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_lld(t_core *core, t_proc *p)
{
	t_instr	*instr;
	t_uint	*dst;
	t_byte	*src;

	instr = &p->instr;
	dst = (t_uint *)instr->args[1];
	if (instr->atypes[0] == T_D)
		*dst = read_data(core, instr, 0);
	else
	{
		src = ABS_POS(core->arena, p->pc, read_data(core, instr, 0));
		*dst = read_core(core, src, REG_SIZE, FALSE);
	}
	return (!*dst);
}
