/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 18:36:50 by sgardner          #+#    #+#             */
/*   Updated: 2019/01/27 05:07:48 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "corestructs.h"
# include "coredef.h"
# include "libft.h"
# include <errno.h>
# include <stdint.h>
# include <string.h>

/*
** #############################################################################
** # CORE FUNCTIOONS                                                           #
** #############################################################################
*/

/*
** coreio.c
*/

void				age_arena(t_byte *epoch);
int32_t				read_arg(t_core *core, t_proc *p, int a);
int32_t				read_core(t_core *core, t_byte *src, int n, t_bool trunc);
void				write_core(t_core *core, t_byte *dst, t_proc *p, int a);

/*
** execution.c
*/

void				execute_war(t_core *core);
void				set_pc(t_core *core, t_proc *p, t_byte *pc, t_uint nproc);

/*
** load.c
*/

t_champ				*find_champ(t_core *core, int32_t id);
t_uint				find_uid(t_core *core);
void				load_champ(t_core *core, const char *path, int pnum);

/*
** main.c
*/

void				usage(void);

/*
** msg.c
*/

void				dump(t_core *core);
void				error(int id, ...);
void				notice(int id, ...);

/*
** ops.c
*/

t_bool				decode(t_byte *arena, t_proc *p, t_instr *instr);

/*
** process.c
*/

void				cull_processes(t_core *core, t_cull *culler);
t_proc				*fork_process(t_core *core, t_proc *p, t_byte *fpc);

/*
** #############################################################################
** # INSTRUCTION SET                                                           #
** #############################################################################
*/

/*
** ./ops/op_*.c
*/

t_bool				op_add(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_aff(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_and(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_fork(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_ld(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_ldi(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_lfork(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_live(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_lld(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_lldi(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_nop(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_or(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_st(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_sti(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_sub(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_xor(t_core *core, t_proc *p, t_instr *instr);
t_bool				op_zjmp(t_core *core, t_proc *p, t_instr *instr);

/*
** #############################################################################
** # CONSTANTS                                                                 #
** #############################################################################
*/

extern const t_op	g_ops[];
extern const t_uint	g_ops_size;
extern const char	*g_errmsg[];
extern const char	*g_notices[];
#endif
