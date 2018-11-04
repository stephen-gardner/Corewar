/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corestructs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 01:24:13 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/04 00:56:54 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESTRUCTS_H
# define CORESTRUCTS_H
# include "coredef.h"
# include "libft.h"

struct s_core;
struct s_proc;
struct s_instr;

typedef struct		s_header
{
	t_uint			magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	t_uint			prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_champ
{
	t_uint			id;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
}					t_champ;

typedef struct		s_op
{
	const char		*name;
	t_bool			(*run)(struct s_core *, struct s_proc *, struct s_instr *);
	t_ushrt			latency;
	t_byte			opcode;
	t_byte			nparams;
	t_byte			ptypes[3];
	t_bool			cbyte : 1;
	t_bool			trunc : 1;
}					t_op;

typedef struct		s_instr
{
	const t_op		*op;
	t_byte			*epc;
	t_byte			*args[3];
	t_byte			atypes[3];
	t_uint			ecycle;
}					t_instr;

typedef struct		s_proc
{
	t_byte			*pc;
	t_champ			*champ;
	t_uint			pid;
	t_uint			lived;
	t_uint			registers[REG_NUMBER];
	t_instr			instr;
	t_bool			carry : 1;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_core
{
	t_byte			arena[MEM_SIZE];
	t_byte			owner[MEM_SIZE];
	t_byte			epoch[MEM_SIZE];
	t_champ			champions[MAX_PLAYERS];
	t_champ			*victor;
	t_proc			*processes;
	t_uint			cycle;
	t_uint			ccycle;
	t_uint			dcycle;
	t_uint			lpid;
	t_uint			lives;
	t_byte			nplayers;
	t_bool			gui : 1;
}					t_core;
#endif
