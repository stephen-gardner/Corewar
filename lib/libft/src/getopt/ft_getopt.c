/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 16:20:06 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/11 17:00:49 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_getopt.h"
#include "libft.h"

char		*g_optarg;
int			g_optind = 1;
int			g_opterr = 1;
int			g_optopt;

static int		opt_error(char *pname, const char *err, const char *optstring)
{
	char	*msg;
	char	*tmp;
	int		len;

	if (g_opterr && *optstring != ':')
	{
		len = ft_strlen(pname) + ft_strlen(err) + 9;
		if (!(msg = ft_memalloc(len)))
			return ('?');
		tmp = msg;
		tmp = ft_stpcpy(tmp, pname);
		tmp = ft_stpcpy(tmp, ": ");
		tmp = ft_stpcpy(tmp, err);
		tmp = ft_stpcpy(tmp, " -- ");
		*tmp++ = g_optopt;
		*tmp = '\n';
		write(STDERR_FILENO, msg, len);
		free(msg);
	}
	return ((*optstring == ':') ? ':' : '?');
}

static t_bool	set_arg(char *const av[], char **pos, const char *op)
{
	t_bool	optional;

	g_optarg = NULL;
	if (*(op + 1) != ':')
		return (TRUE);
	g_optarg = (**pos) ? *pos : av[g_optind];
	optional = (*op && *(op + 2) == ':');
	if (optional && g_optarg && *g_optarg == '-')
		g_optarg = NULL;
	else
		++g_optind;
	*pos = NULL;
	return (g_optarg != NULL || optional);
}

static int		process_arg(char *const av[], const char *optstring)
{
	static char	*pos;
	const char	*op;

	if (!pos || !*pos)
		pos = av[g_optind] + 1;
	g_optopt = *pos++;
	if (!*pos)
		++g_optind;
	if (!(op = ft_strchr(optstring, g_optopt)))
		return (opt_error(av[0], "illegal option", optstring));
	if (!set_arg(av, &pos, op))
		return (opt_error(av[0], "option requires an argument", optstring));
	return (g_optopt);
}

int				ft_getopt(int ac, char *const av[], const char *optstring)
{
	if (g_optind == 1)
	{
		g_optarg = NULL;
		g_optopt = '\0';
	}
	if (g_optind < ac)
	{
		if (*av[g_optind] != '-' || !*(av[g_optind] + 1))
		{
			if (*optstring != '-')
				return (-1);
			g_optarg = av[g_optind++];
			return ((g_optopt = '\1'));
		}
		if (!ft_strcmp(av[g_optind], "--"))
		{
			g_optopt = '-';
			++g_optind;
			return (-1);
		}
		return (process_arg(av, optstring));
	}
	return (-1);
}
