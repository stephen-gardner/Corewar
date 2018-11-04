/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 00:30:56 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/04 01:03:18 by sgardner         ###   ########.fr       */
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
		if (core->cycle - (*procs)->lived >= core->ccycle)
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
		core->lives = 0;
		if (core->ccycle > CYCLE_DELTA)
			core->ccycle -= CYCLE_DELTA;
		else
			core->ccycle = 0;
	}
	return ((core->ccycle > 0) ? core->ccycle : 1);
}

static void	exec_op(t_core *core, t_instr *instr, t_byte *pc)
{
	if ((t_uint)(*pc - 1) < g_ops_size)
		instr->op = &g_ops[*pc - 1];
	else
		instr->op = &g_ops[g_ops_size - 1];
	instr->epc = ABS_POS(core->arena, pc, 1);
	instr->ecycle = core->cycle + instr->op->latency;
}

void		execute_processes(t_core *core, t_proc *p)
{
	t_instr	*instr;

	while (p)
	{
		instr = &p->instr;
		if (core->cycle == instr->ecycle)
		{
			if (instr->op->cbyte && !decode(core->arena, p, instr))
				instr->op = &g_ops[g_ops_size - 1];
			p->carry = instr->op->run(core, p, instr);
			p->pc = instr->epc;
			exec_op(core, instr, p->pc);
		}
		p = p->next;
	}
}

t_proc		*fork_process(t_core *core, t_proc *p, t_byte *fpc)
{
	t_proc	*clone;

	if (!(clone = ft_memalloc(sizeof(t_proc))))
		SYS_ERR;
	if (p)
		ft_memcpy(clone, p, sizeof(t_proc));
	clone->next = core->processes;
	core->processes = clone;
	clone->pc = fpc;
	clone->pid = ++core->lpid;
	exec_op(core, &clone->instr, clone->pc);
	return (clone);
}
