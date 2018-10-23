/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 18:36:50 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/23 07:09:34 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "corestructs.h"
# include "coredef.h"
# include "libft.h"

/*
** load.c
*/

t_bool				load_champ(t_core *core, const char *path);

/*
** process.c
*/

t_proc				*add_process(t_core *core, t_uint id);
t_uint				cull_processes(t_core *core);
t_proc				*fork_process(t_core *core, t_proc *process);

/*
** util.c
*/

t_bool				error(const char *fmt, ...);

/*
** #############################################################################
** # CONSTANTS                                                                 #
** #############################################################################
*/

extern const t_op	g_ops[];
#endif
