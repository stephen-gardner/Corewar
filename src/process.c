/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 00:30:56 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/29 21:53:02 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

/*
** Instantiates new process with given id in r1 and adds it to the front of the
**  process list. Returns pointer to process.
*/

t_proc		*add_process(t_core *core, t_uint id)
{
	t_proc	*process;

	if (!(process = ft_memalloc(sizeof(t_proc))))
		SYS_ERR;
	process->registers[0] = id;
	process->next = core->processes;
	core->processes = process;
	return (process);
}

/*
** Kills processes that have not yet lived, and resets the lived state for
**  survivors. Returns number of processes that have been culled.
*/

t_uint		cull_processes(t_core *core)
{
	t_proc	**processes;
	t_proc	*weakling;
	t_uint	count;

	count = 0;
	processes = &core->processes;
	while (*processes)
	{
		if (!(*processes)->lived)
		{
			weakling = *processes;
			*processes = (*processes)->next;
			free(weakling);
			++count;
			continue ;
		}
		(*processes)->lived = FALSE;
		processes = &(*processes)->next;
	}
	return (count);
}

// TODO: Decide on behavior for failed decode

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
		if (!instr->op)
			exec_op(core, instr, p->pc);
		if (core->cycle == instr->ecycle)
		{
			if (instr->op->cbyte && !decode(core->arena, p))
				instr->op = &g_ops[g_ops_size - 1];
			p->carry = instr->op->run(core, p);
			p->pc = instr->epc;
			exec_op(core, instr, p->pc);
		}
		p = p->next;
	}
}

/*
** Duplicates given process and adds it to the front of the process list.
**  Returns pointer to clone.
*/

t_proc		*fork_process(t_core *core, t_proc *process, t_byte *fpc)
{
	t_proc	*clone;

	if (!(clone = malloc(sizeof(t_proc))))
		SYS_ERR;
	ft_memcpy(clone, process, sizeof(t_proc));
	clone->next = core->processes;
	core->processes = clone;
	clone->pc = fpc;
	exec_op(core, &clone->instr, clone->pc);
	return (clone);
}
