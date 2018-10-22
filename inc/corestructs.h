/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corestructs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 01:24:13 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/22 01:39:49 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESTRUCTS_H
# define CORESTRUCTS_H
# include "coredef.h"
# include "libft.h"

typedef struct		s_champ
{
	t_uint			id;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
}					t_champ;

typedef struct		s_proc
{
	t_byte			*pc;
	t_byte			registers[REG_NUMBER][REG_SIZE];
	t_bool			carry;
	t_bool			lived;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_op
{
	t_uint			opcode;
	t_uint			latency;
	t_uint			nparams;
	t_bool			cbyte;
	t_bool			trunc;
	t_byte			ptypes[3];
}					t_op;

typedef struct		s_cmd
{
	t_proc			*process;
	t_op			*op;
	t_uint			ecycle;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_core
{
	t_byte			arena[MEM_SIZE];
	t_uint			cycle;
	t_champ			champions[MAX_PLAYERS];
	t_uint			nplayers;
	t_coreproc		*processes;
	t_cmd			*schedule;
}					t_core;
#endif
