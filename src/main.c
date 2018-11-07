/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 20:53:34 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/07 04:12:55 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ft_getopt.h"
#include <limits.h>
#include <stdlib.h>

/*
** Reports the winning player(s).
*/

static void		aftermath(t_core *core, t_champ *victor)
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
		MSG(ANNOUNCE_WINNER, ID(victor->id), victors[i]->name);
		MSG(CHAMP_COMMENT, victors[i]->comment);
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

void			execute_war(t_core *core)
{
	while (TRUE)
	{
		if (++core->cycle > core->dcycle)
			dump(core);
		execute_processes(core, core->processes);
		if (core->cycle >= core->cull.ccycle)
			cull_processes(core, &core->cull, &core->processes);
		if (!core->processes)
			return (aftermath(core, core->victor));
		if (core->gui && !(core->cycle % GFX_AGE_SPEED))
			age_arena(core->epoch);
		if (core->gui)
			break ;
	}
}

/*
** Find first available, unique champion ID, starting with the ID of the
**  previous champion.
*/

static t_uint	find_id(t_core *core)
{
	int32_t	id;
	int		i;

	if (!core->nplayers)
		return (1);
	i = -1;
	id = core->champions[core->nplayers - 1].id + 1;
	while (++i < core->nplayers - 1)
	{
		if (id == core->champions[i].id)
		{
			i = -1;
			++id;
		}
	}
	return (id);
}

/*
** Parse command line arguments and return array with paths to champion
**  binaries.
** Players are allowed to be passed the same ID for team play.
*/

static char		**parse_args(t_core *core, int ac, char *const av[])
{
	static char	*paths[MAX_PLAYERS];
	char		f;

	while ((f = ft_getopt(ac, av, "-d:gn:q")) != -1)
	{
		if (f == 'd')
			core->dcycle = ft_atoi(g_optarg);
		else if (f == 'g')
			core->gui = TRUE;
		else if (f == 'n')
			core->champions[core->nplayers].id = ft_atoi(g_optarg);
		else if (f == 'q')
			core->quiet = TRUE;
		else if (f == '\1')
		{
			if (core->nplayers == MAX_PLAYERS)
				ERR(TOO_MANY_CHAMPS);
			if (!core->champions[core->nplayers].id)
				core->champions[core->nplayers].id = find_id(core);
			paths[core->nplayers++] = g_optarg;
		}
		else if (f == '?')
			error(USAGE);
	}
	return (paths);
}

/*
** Champion IDs are made negative for the core.
** We allow the GUI to execute the war cycle by cycle.
*/

int				main(int ac, char *av[])
{
	t_core	core;
	char	**paths;
	int		i;

	ft_memset(&core, 0, sizeof(t_core));
	core.cull.ctd = CYCLE_TO_DIE;
	core.cull.ccycle = CYCLE_TO_DIE;
	core.dcycle = -1;
	paths = parse_args(&core, ac, av);
	if (!core.nplayers)
		ERR(NO_PLAYERS);
	i = -1;
	while (++i < core.nplayers)
	{
		core.champions[i].id = ID(core.champions[i].id);
		load_champ(&core, paths[i], i);
	}
	if (core.gui)
	{
		MSG(LAUNCH_GUI);
	}
	else
		execute_war(&core);
	return (EXIT_SUCCESS);
}
