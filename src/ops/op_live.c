/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 07:26:58 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/06 21:20:28 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <limits.h>

t_bool	op_live(t_core *core, t_proc *p, t_instr *instr)
{
	int32_t	id;
	t_champ	*champ;

	id = read_core(core, instr->epc, DIR_SIZE, FALSE);
	if ((champ = find_champ(core, id)))
	{
		p->champ = champ;
		core->victor = champ;
		++core->cull.plives[champ - core->champions];
		++core->cull.plives_total;
		notice(ANNOUNCE_LIVE, ID(champ->id), champ->name);
	}
	instr->epc = ABS_POS(core->arena, instr->epc, DIR_SIZE);
	p->lcycle = core->cycle;
	++core->cull.nbr_lives;
	return (p->carry);
}
