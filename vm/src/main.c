/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 20:53:34 by sgardner          #+#    #+#             */
/*   Updated: 2019/01/25 00:22:43 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gui.h"
#include "ft_getopt.h"
#include "ft_printf.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

/*
** Parse command line arguments and return array with paths to champion
**  binaries.
** Players are allowed to be passed the same ID for team play.
*/

static char	**parse_args(t_core *core, int ac, char *const av[])
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
				core->champions[core->nplayers].id = find_uid(core);
			paths[core->nplayers++] = g_optarg;
		}
		else if (f == '?')
			usage();
	}
	return (paths);
}

/*
** Champion IDs are made negative for the core.
** We allow the GUI to execute the war cycle by cycle.
*/

int			main(int ac, char *av[])
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
		core.champions[i].id = -core.champions[i].id;
		load_champ(&core, paths[i], i);
	}
	if (core.gui)
	{
		MSG(LAUNCH_GUI);
		return (gui_init(&core));
	}
	else
		execute_war(&core);
	return (EXIT_SUCCESS);
}

#define USAGE(m)	ft_dprintf(STDERR_FILENO, m)

void		usage(void)
{
	USAGE("Usage: corewar [-g] [-d cycle] [-q] <[-n id] champion ...>\n");
	USAGE("   -g       : Display GUI\n");
	USAGE("   -d cycle : Dumps state of core at specified cycle and exits\n");
	USAGE("   -q       : Silences aff and live instruction messages\n");
	USAGE("   -n id    : Specifies champion ID (can be used for team play)\n");
	exit(EXIT_FAILURE);
}
