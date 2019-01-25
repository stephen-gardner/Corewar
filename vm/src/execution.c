/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 00:13:38 by sgardner          #+#    #+#             */
/*   Updated: 2019/01/25 00:39:35 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gui.h"

/*
** Reports the winning player(s).
*/

static void	aftermath(t_core *core, t_champ *victor)
{
	t_champ	*victors[MAX_PLAYERS];
	int		n;
	int		i;

	MSG(WAR_OVER, core->cycle);
	if (!victor)
	{
		MSG(ANNOUNCE_LOSERS);
		return ;
	}
	n = 0;
	i = -1;
	while (++i < core->nplayers)
	{
		if (core->champions[i].id == victor->id)
			victors[n++] = &core->champions[i];
	}
	if (n > 1)
		MSG(ANNOUNCE_WINNER_TEAM, victor->name);
	i = -1;
	while (++i < n)
	{
		MSG(ANNOUNCE_WINNER, -victor->id, victors[i]->name);
		MSG(CHAMP_COMMENT, victors[i]->comment);
	}
}

/*
** Assigns instruction to process, and sets the epc (or pc, if NOP) to one byte
**  ahead of pc.
** The current cycle counts towards the instruction execution time.
*/

static void	exec_op(t_core *core, t_proc *p, t_instr *instr)
{
	instr->epc = ABS_POS(core->arena, p->pc, 1);
	if ((t_uint)(*p->pc - 1) < g_ops_size)
	{
		instr->op = &g_ops[*p->pc - 1];
		instr->ecycle = core->cycle + instr->op->latency - 1;
	}
	else
	{
		instr->op = NOP;
		p->pc = instr->epc;
	}
}

/*
** Executes the proces list in order.
** If current instruction is a NOP (also the initial instruction), the process
**  tries to execute the instruction at its PC. If the instruction is
**  invalid (NOP), the process moves forward by a single byte and waits.
** Otherwise, the current instruction is executed if scheduled.
** If the instruction has a coding byte, the instruction is not executed if the
**  coding byte is invalid.
**
** WARNING: Fork instructions can cause the process pointer in the while loop
**  to point to an invalid address.
*/

static void	execute_processes(t_core *core)
{
	t_proc	*p;
	t_instr	*instr;
	t_uint	i;

	i = core->procpool.size;
	while (i--)
	{
		p = &core->procpool.procs[i];
		instr = &p->instr;
		if (!instr->op->opcode)
			exec_op(core, p, instr);
		else if (core->cycle == instr->ecycle)
		{
			if (instr->op->opcode == 0x0C || instr->op->opcode == 0x0F)
				instr->op->run(core, p, instr);
			else
			{
				if (!instr->op->cbyte || decode(core->arena, p, instr))
					p->carry = instr->op->run(core, p, instr);
				p->pc = instr->epc;
				instr->op = NOP;
			}
		}
	}
}

/*
** Main game loop.
** Core cycle starts at 1. Core dump of previous cycle happens before
**  execution if scheduled.
** Processes are executed in order of newest to oldest.
** Processes are then culled every CYCLE_TO_DIE cycles.
** If GUI is in use, we age the arena every GFX_AGE_SPEED cycles and break.
*/

void		execute_war(t_core *core)
{
	while (TRUE)
	{
		if (++core->cycle > core->dcycle)
			dump(core);
		execute_processes(core);
		if (core->cycle >= core->cull.ccycle)
			cull_processes(core, &core->cull);
		if (!core->procpool.size)
			return (aftermath(core, core->victor));
		if (core->gui && !(core->cycle % GFX_AGE_SPEED))
			age_arena(core->epoch);
		if (core->gui)
			break ;
	}
}
