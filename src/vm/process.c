/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 00:30:56 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/06 00:17:17 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

t_uint		cull_processes(t_core *core, t_proc **procs)
{
	static t_uint	checks;
	t_proc			*weakling;

	while (*procs)
	{
		if (core->cycle - (*procs)->lcycle >= core->ccycle)
		{
			weakling = *procs;
			*procs = (*procs)->next;
			free(weakling);
			continue ;
		}
		procs = &(*procs)->next;
	}
	if (++checks >= MAX_CHECKS || core->lives >= NBR_LIVE)
	{
		checks = 0;
		core->ccycle = (core->ccycle > CYCLE_DELTA) ?
			core->ccycle - CYCLE_DELTA : 0;
	}
	core->lives = 0;
	return ((core->ccycle > 0) ? core->ccycle : 1);
}

#define NOP	&g_ops[g_ops_size - 1]

static void	exec_op(t_core *core, t_instr *instr, t_byte *pc)
{
	if ((t_uint)(*pc - 1) < g_ops_size)
		instr->op = &g_ops[*pc - 1];
	else
		instr->op = NOP;
	instr->epc = ABS_POS(core->arena, pc, 1);
	instr->ecycle = core->cycle + instr->op->latency - 1;
}

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
