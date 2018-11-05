/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 20:53:34 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/04 00:52:44 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ft_getopt.h"
#include <limits.h>
#include <stdlib.h>

static void		aftermath(t_core *core, t_champ *victor)
{
	t_champ	*victors[MAX_PLAYERS];
	int		n;
	int		i;

	if (victor)
	{
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
	else
		MSG(ANNOUNCE_LOSERS);
}

void			execute_war(t_core *core)
{
	static t_uint	countdown = CYCLE_TO_DIE;

	while (TRUE)
	{
		if (++core->cycle > core->dcycle)
			dump(core);
		execute_processes(core, core->processes);
		if (!--countdown)
			countdown = cull_processes(core, &core->processes);
		if (!core->processes)
			return (aftermath(core, core->victor));
		if (!(core->cycle % 10))
			age_arena(core->epoch);
		if (core->gui)
			break ;
	}
}

static t_uint	find_id(t_core *core)
{
	t_uint	id;
	int		i;

	if (!core->nplayers)
		return (0);
	i = -1;
	id = core->champions[core->nplayers - 1].id + 1;
	while (++i < core->nplayers - 1)
	{
		if (id == core->champions[core->nplayers].id)
		{
			i = -1;
			++id;
		}
	}
	return (id);
}

static char		**parse_args(t_core *core, int ac, char *const av[])
{
	static char	*paths[MAX_PLAYERS];
	char		f;

	while ((f = ft_getopt(ac, av, "-d:gn:")) != -1)
	{
		if (f == 'd')
			core->dcycle = ft_atoi(g_optarg);
		else if (f == 'g')
			core->gui = TRUE;
		else if (f == 'n')
			core->champions[core->nplayers].id = ft_atoi(g_optarg);
		else if (f == '\1')
		{
			if (core->nplayers == MAX_PLAYERS)
				ERR(TOO_MANY_CHAMPS);
			if (!core->champions[core->nplayers].id)
				core->champions[core->nplayers].id = find_id(core);
			paths[core->nplayers++] = g_optarg;
		}
		else
			exit(EXIT_FAILURE);
	}
	return (paths);
}

int				main(int ac, char *av[])
{
	t_core	core;
	char	**paths;
	int		i;

	ft_memset(&core, 0, sizeof(t_core));
	core.ccycle = CYCLE_TO_DIE;
	core.dcycle = -1;
	core.victor = NULL;
	paths = parse_args(&core, ac, av);
	if (!core.nplayers)
		ERR(NO_PLAYERS);
	i = -1;
	while (++i < core.nplayers)
	{
		core.champions[i].id = UINT_MAX - core.champions[i].id;
		load_champ(&core, paths[i], i);
	}
	if (core.gui)
	{
		MSG(LAUNCH_GUI);
        corewar_gui_init(&core);
	}
	else
		execute_war(&core);
	return (EXIT_SUCCESS);
}