/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 20:53:34 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/24 08:21:08 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ft_getopt.h"
#include "ft_printf.h"
#include <limits.h>
#include <stdlib.h>

static t_uint	find_id(t_core *core)
{
	t_uint	id;
	int		i;

	if (!core->nplayers)
		return (0);
	i = 0;
	id = core->champions[core->nplayers - 1].id + 1;
	while (i < core->nplayers - 1)
	{
		if (id == core->champions[core->nplayers].id)
		{
			i = 0;
			++id;
		}
		++i;
	}
	return (id);
}

static char		**parse_args(t_core *core, int ac, char *const av[])
{
	static char	*paths[MAX_PLAYERS];
	char		f;

	while ((f = ft_getopt(ac, av, "-d:n:")) != -1)
	{
		if (f == 'd')
			core->dcycle = ft_atoi(g_optarg);
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
	char	**paths;
	t_core	core;
	int		i;

	ft_memset(&core, 0, sizeof(t_core));
	core.dcycle = -1;
	paths = parse_args(&core, ac, av);
	if (!core.nplayers)
		return (1);
	i = 0;
	while (i < core.nplayers)
	{
		core.champions[i].id = UINT_MAX - core.champions[i].id;
		load_champ(&core, paths[i], i);
		++i;
	}
	dump(&core);
	return (EXIT_SUCCESS);
}
