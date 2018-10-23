/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corestructs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 01:24:13 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/23 02:11:07 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESTRUCTS_H
# define CORESTRUCTS_H
# include "coredef.h"
# include "libft.h"

typedef struct		s_op
{
	const char		*instr;
	t_ushrt			latency;
	t_byte			opcode;
	t_byte			nparams;
	t_byte			ptypes[3];
	t_bool			cbyte : 1;
	t_bool			trunc : 1;
}					t_op;

typedef struct		s_proc
{
	t_uint			registers[REG_NUMBER];
	t_byte			*pc;
	t_op			*op;
	t_uint			ecycle;
	t_bool			carry : 1;
	t_bool			lived : 1;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_champ
{
	t_uint			id;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
}					t_champ;

typedef struct		s_core
{
	t_byte			arena[MEM_SIZE];
	t_byte			owner[MEM_SIZE];
	t_proc			*processes;
	t_champ			champions[MAX_PLAYERS];
	t_uint			nplayers;
	t_uint			cycle;
}					t_core;
#endif
