/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 00:30:56 by sgardner          #+#    #+#             */
/*   Updated: 2019/01/27 22:18:20 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

/*
** If live has been called at least NBR_LIVE times since the last check, or
**  MAX_CHECKS checks have happened, CYCLE_TO_DIE is reduced by CYCLE_DELTA.
*/

static void	schedule_culling(t_core *core, t_cull *cull)
{
	int	i;

	if (++cull->checks >= MAX_CHECKS || cull->nbr_lives >= NBR_LIVE)
	{
		cull->checks = 0;
		cull->ctd = (cull->ctd > CYCLE_DELTA) ? cull->ctd - CYCLE_DELTA : 0;
		i = core->nplayers;
		while (i--)
			core->champions[i].plives = 0;
		cull->plives = 0;
	}
	cull->nbr_lives = 0;
	cull->ccycle = core->cycle + cull->ctd;
}

/*
** Frees up unused memory in the process pool.
*/

static void	drain_pool(t_procpool *pool)
{
	pool->maxsize /= 2;
	pool->procs = realloc(pool->procs, sizeof(t_proc) * pool->maxsize);
	pool->meta = realloc(pool->meta, sizeof(t_meta) * pool->maxsize);
	if (!pool->procs || !pool->meta)
		SYS_ERR;
}

#define CULLED(meta, i)	(meta[i].pos == CULL_PROC)

/*
** Shifts all living processes to a contiguous memory section.
*/

static void	defrag_pool(t_procpool *pool, t_uint start, t_uint killed)
{
	t_meta	*meta;
	t_uint	end;

	end = start + 1;
	meta = pool->meta;
	while (end < pool->size)
	{
		while (start < pool->size && !CULLED(meta, start))
			++start;
		if (end < start)
			end = start + 1;
		while (end < pool->size && CULLED(meta, end))
			++end;
		while (end < pool->size && CULLED(meta, start) && !CULLED(meta, end))
		{
			meta[start] = meta[end];
			meta[end].pos = CULL_PROC;
			pool->procs[start++] = pool->procs[end++];
		}
	}
	pool->size -= killed;
	if (pool->size > 32 && pool->size <= (pool->maxsize / 3))
		drain_pool(pool);
}

/*
** Kills processes that have not yet called the live instruction, and schedules
**  the next culling.
*/

void		cull_processes(t_core *core, t_cull *cull)
{
	t_procpool	*pool;
	t_proc		*p;
	t_uint		start;
	t_uint		killed;
	t_uint		i;

	start = 0;
	killed = 0;
	pool = &core->procpool;
	i = pool->size;
	while (i--)
	{
		p = &pool->procs[i];
		if (core->cycle - p->lcycle >= cull->ctd)
		{
			start = i;
			pool->meta[i].pos = CULL_PROC;
			++killed;
		}
	}
	if (killed)
		defrag_pool(pool, start, killed);
	schedule_culling(core, cull);
}

/*
** Spawns a new process and adds it to the "front" of the execution list.
** Instruction to execute starts with a NOP to begin execution on next cycle.
** If process is a fork of another, all data (except for the PC and pid) is
**  copied to the child process from the parent process.
**
** WARNING: Resizing the process pool may cause the parent process to shift to
**  a new memory address.
*/

t_proc		*fork_process(t_core *core, t_proc *p, t_byte *fpc)
{
	static t_uint	lpid;
	t_procpool		*pool;
	t_proc			*clone;

	pool = &core->procpool;
	if (!pool->procs || pool->size == pool->maxsize)
	{
		clone = pool->procs;
		pool->maxsize = (pool->maxsize) ? pool->maxsize << 1 : 32;
		pool->procs = realloc(pool->procs, sizeof(t_proc) * pool->maxsize);
		pool->meta = realloc(pool->meta, sizeof(t_meta) * pool->maxsize);
		if (!pool->procs || !pool->meta)
			SYS_ERR;
		ft_memset(pool->procs + pool->size, 0,
			sizeof(t_proc) * (pool->maxsize - pool->size));
		p = (p && pool->procs != clone) ? pool->procs + (p - clone) : p;
	}
	clone = &pool->procs[pool->size];
	if (p)
		ft_memcpy(clone, p, sizeof(t_proc));
	clone->pid = ++lpid;
	clone->instr.op = NOP;
	set_pc(core, clone, fpc, pool->size);
	pool->meta[pool->size++].ecycle = core->cycle + 1;
	return (clone);
}
