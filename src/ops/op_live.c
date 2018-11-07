/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 07:26:58 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/07 15:09:58 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <limits.h>

/*
** Argument is 4 bytes specifying champion ID.
** If ID is of a valid champion, we set the process' champ to it, and announce
**  that a process has lived for that champion.
** A process is considered to live even if the champion ID is invalid, and it
**  always counts towards NBR_LIVES.
*/

t_bool	op_live(t_core *core, t_proc *p, t_instr *instr)
{
	int32_t	id;
	t_champ	*champ;

	id = read_core(core, instr->epc, DIR_SIZE, FALSE);
	if ((champ = find_champ(core, id)))
	{
		p->champ = champ;
		core->victor = champ;
		champ->last_live = core->cycle;
		++champ->plives;
		++core->cull.plives;
		if (!core->quiet)
			notice(ANNOUNCE_LIVE, -champ->id, champ->name);
	}
	instr->epc = ABS_POS(core->arena, instr->epc, DIR_SIZE);
	p->lcycle = core->cycle;
	++core->cull.nbr_lives;
	return (p->carry);
}
