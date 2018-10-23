/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 00:30:56 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/23 02:19:29 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

/*
** Instantiates new process with given id in r1 and adds it to the front of the
**  process list. Returns pointer to process.
*/

t_proc	*add_process(t_core *core, t_uint id)
{
	t_proc	*process;

	if (!(process = ft_memalloc(sizeof(t_proc))))
		return (NULL);
	process->registers[0] = id;
	process->next = core->processes;
	core->processes = process;
	return (process);
}

/*
** Kills processes that have not yet lived, and resets the lived state for
**  survivors. Returns number of processes that have been culled.
*/

t_uint	cull_processes(t_core *core)
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

/*
** Duplicates given process and adds it to the front of the process list.
**  Returns pointer to clone.
*/

t_proc	*fork_process(t_core *core, t_proc *process)
{
	t_proc	*clone;

	if (!(clone = malloc(sizeof(t_proc))))
		return (NULL);
	ft_memcpy(clone, process, sizeof(t_proc));
	clone->op = NULL;
	clone->next = core->processes;
	core->processes = clone;
	return (clone);
}
