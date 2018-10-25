/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 18:36:50 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/25 05:16:33 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "corestructs.h"
# include "coredef.h"
# include "libft.h"
# include <errno.h>
# include <string.h>

/*
** load.c
*/

void				load_champ(t_core *core, const char *path, int pnum);

/*
** msg.c
*/

void				dump(t_core *core);
void				error(int id, ...);
void				notice(int id, ...);

/*
** process.c
*/

t_proc				*add_process(t_core *core, t_uint id);
t_uint				cull_processes(t_core *core);
t_proc				*fork_process(t_core *core, t_proc *process);

/*
** #############################################################################
** # CONSTANTS                                                                 #
** #############################################################################
*/

extern const t_op	g_ops[];
extern const char	*g_errmsg[];
extern const char	*g_notices[];
#endif
