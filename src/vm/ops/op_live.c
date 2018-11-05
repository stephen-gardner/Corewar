/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 07:26:58 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/03 04:03:46 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <limits.h>

t_bool	op_live(t_core *core, t_proc *p)
{
	t_instr	*instr;
	t_uint	id;
	int		i;

	instr = &p->instr;
	id = read_core(core, instr->epc, DIR_SIZE, FALSE);
	i = 0;
	while (i < core->nplayers && core->champions[i].id != id)
		++i;
	if (i < core->nplayers)
	{
		p->champ = &core->champions[i];
		core->victor = &core->champions[i];
		notice(ANNOUNCE_LIVE, ID(core->victor->id), core->victor->name);
	}
	instr->epc = ABS_POS(core->arena, instr->epc, DIR_SIZE);
	p->lived = core->cycle;
	++core->lives;
	return (p->carry);
}