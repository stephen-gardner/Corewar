/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 00:30:56 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/06 21:11:59 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

#define NOP	&g_ops[g_ops_size - 1]

/*
** Kills processes that have not yet called the live instruction.
** If live has been called at least NBR_LIVE times since the last check, or
**  MAX_CHECKS checks have happened, CYCLE_TO_DIE is reduced by CYCLE_DELTA.
*/

void		cull_processes(t_core *core, t_cull *cull, t_proc **p)
{
	t_proc	*weakling;
	int		i;

	while (*p)
	{
		if (core->cycle - (*p)->lcycle >= cull->ctd)
		{
			weakling = *p;
			*p = (*p)->next;
			free(weakling);
			continue ;
		}
		p = &(*p)->next;
	}
	if (++cull->checks >= MAX_CHECKS || cull->nbr_lives >= NBR_LIVE)
	{
		cull->checks = 0;
		cull->ctd = (cull->ctd > CYCLE_DELTA) ? cull->ctd - CYCLE_DELTA : 0;
		i = -1;
		while (++i < core->nplayers)
			cull->plives[i] = 0;
		cull->plives_total = 0;
	}
	cull->nbr_lives = 0;
	cull->ccycle = core->cycle + cull->ctd;
}

/*
** Assigns instruction to process, and sets the epc to one byte ahead of pc.
** The current cycle counts towards the instruction execution time.
*/

static void	exec_op(t_core *core, t_instr *instr, t_byte *pc)
{
	if ((t_uint)(*pc - 1) < g_ops_size)
		instr->op = &g_ops[*pc - 1];
	else
		instr->op = NOP;
	instr->epc = ABS_POS(core->arena, pc, 1);
	instr->ecycle = core->cycle + instr->op->latency - 1;
}

/*
** Executes the proces list in order.
** If current instruction is a NOP (also the initial instruction), the process
**  tries to execute the instruction at its PC. If the instruction is
**  invalid (NOP), the process moves forward by a single byte and waits.
** Otherwise, the current instruction is executed if scheduled.
** If the instruction has a coding byte, the instruction is not executed if the
**  coding byte is invalid.
*/

void		execute_processes(t_core *core, t_proc *p)
{
	t_instr	*instr;

	while (p)
	{
		instr = &p->instr;
		if (!instr->op->opcode)
		{
			exec_op(core, instr, p->pc);
			if (instr->op == NOP)
				p->pc = instr->epc;
		}
		else if (core->cycle == instr->ecycle)
		{
			if (!instr->op->cbyte || decode(core->arena, p, instr))
				p->carry = instr->op->run(core, p, instr);
			p->pc = instr->epc;
			instr->op = NOP;
		}
		p = p->next;
	}
}

/*
** Spawns a new process and adds it to the front of the execution list.
** Instruction to execute starts with a NOP to begin execution on next cycle.
** If process is a fork of another, all data (except for the PC and pid) is
**  copied to the child process from the parent process.
*/

t_proc		*fork_process(t_core *core, t_proc *p, t_byte *fpc)
{
	static t_uint	lpid;
	t_proc			*clone;

	if (!(clone = ft_memalloc(sizeof(t_proc))))
		SYS_ERR;
	if (p)
		ft_memcpy(clone, p, sizeof(t_proc));
	clone->next = core->processes;
	core->processes = clone;
	clone->pc = fpc;
	clone->pid = ++lpid;
	clone->instr.op = NOP;
	return (clone);
}
