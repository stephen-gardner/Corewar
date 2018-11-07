/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corestructs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 01:24:13 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/07 03:08:23 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESTRUCTS_H
# define CORESTRUCTS_H
# include "coredef.h"
# include "libft.h"
# include <stdint.h>

struct s_core;
struct s_proc;
struct s_instr;

/*
** -----------------------------------------------------------------------------
** | {struct s_header}                                              <t_header> |
** | File header for loading champions                                         |
** |---------------------------------------------------------------------------|
** | magic     | Indentifies file type as a *.cor                              |
** | prog_name | Name of champion                                              |
** | prog_size | Size of champions executable code                             |
** | comment   | Champion's description                                        |
** -----------------------------------------------------------------------------
*/

typedef struct		s_header
{
	uint32_t		magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	uint32_t		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

/*
** -----------------------------------------------------------------------------
** | {struct s_champ}                                                <t_champ> |
** | Champion data                                                             |
** |---------------------------------------------------------------------------|
** | id      | ID of champion (configurable with -n in command line)           |
** | plives  | Number of lives for champion for current period                 |
** | name    | Name of champion                                                |
** | comment | Champion's description                                          |
** -----------------------------------------------------------------------------
*/

typedef struct		s_champ
{
	int32_t			id;
	t_uint			plives;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
}					t_champ;

/*
** -----------------------------------------------------------------------------
** | {struct s_op}                                                      <t_op> |
** | For instruction settings                                                  |
** |---------------------------------------------------------------------------|
** | name    | Name of the instruction                                         |
** | run     | Function pointer to dispatch instruction                        |
** | latency | Number of cycles instruction takes to execute                   |
** | opcode  | Instruction's byte code                                         |
** | nparams | Number of required parameters                                   |
** | ptypes  | Accepted argument types; use ac - 1 for index                   |
** | cbyte   | TRUE if instruction uses a coding byte                          |
** | trunc   | TRUE if direct value arguments will have IND_SIZE bytes         |
** -----------------------------------------------------------------------------
*/

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

/*
** -----------------------------------------------------------------------------
** | {struct s_instr}                                                <t_instr> |
** | Instruction being executed                                                |
** |---------------------------------------------------------------------------|
** | op     | Pointer to instruction settings                                  |
** | epc    | Pointer to position of owning process in core->arena after       |
** |        |  the operation is complete                                       |
** | args   | Pointer to arguments for instruction                             |
** | atypes | Specifies type for args with same index                          |
** | ecycle | Cycle when operation will complete                               |
** -----------------------------------------------------------------------------
*/

typedef struct		s_instr
{
	const t_op		*op;
	t_byte			*epc;
	t_byte			*args[3];
	t_byte			atypes[3];
	t_uint			ecycle;
}					t_instr;

/*
** -----------------------------------------------------------------------------
** | {struct s_proc}                                                  <t_proc> |
** | All data pertaining to a given process                                    |
** |---------------------------------------------------------------------------|
** | pc        | Position of process in core->arena                            |
** | champ     | Pointer to last champion process lived for                    |
** | registers | The processes "registers"--it's more like memory              |
** | instr     | Instruction being executed                                    |
** | pid       | Process PID                                                   |
** | lcycle    | Last cycle when process called live                           |
** | carry     | The "carry" flag; TRUE when last operation returned 0         |
** | next      | Next process in list                                          |
** -----------------------------------------------------------------------------
*/

typedef struct		s_proc
{
	t_byte			*pc;
	t_champ			*champ;
	int32_t			registers[REG_NUMBER];
	t_instr			instr;
	t_uint			pid;
	t_uint			lcycle;
	t_bool			carry : 1;
	struct s_proc	*next;
}					t_proc;

/*
** -----------------------------------------------------------------------------
** | {struct s_cull}                                                  <t_cull> |
** | Keeps track of lives and process culling schedule                         |
** |---------------------------------------------------------------------------|
** | ccycle       | Cycle when next culling takes place                        |
** | ctd          | The current CYCLE_TO_DIE                                   |
** | checks       | Number of cullings done towards MAX_CHECKS for period      |
** | nbr_lives    | Number of lives called by processes since last culling     |
** | plives       | Total number of valid lives for period                     |
** -----------------------------------------------------------------------------
*/

typedef struct		s_cull
{
	t_uint			ccycle;
	t_uint			ctd;
	t_uint			checks;
	t_uint			nbr_lives;
	t_uint			plives;
}					t_cull;

/*
** -----------------------------------------------------------------------------
** | {struct s_core}                                                  <t_core> |
** | Main struct                                                               |
** |---------------------------------------------------------------------------|
** | arena     | The Core                                                      |
** | owner     | GUI - Says which data in the core belongs to which champion;  |
** |           |  stores the index (+1) to the champion in core->champions     |
** | epoch     | GUI - Age of the data in the core                             |
** | champions | The loaded players                                            |
** | cull      | Keeps track of lives and culling schedule                     |
** | victor    | Pointer to last champion to have a process call live for it   |
** | processes | Linked list of processes still alive                          |
** | cycle     | Current cycle                                                 |
** | dcycle    | The cycle that the core will be dumped                        |
** | nplayers  | Number of champions loaded                                    |
** | gui       | TRUE if the GUI is being used                                 |
** -----------------------------------------------------------------------------
*/

typedef struct		s_core
{
	t_byte			arena[MEM_SIZE];
	t_byte			owner[MEM_SIZE];
	t_byte			epoch[MEM_SIZE];
	t_champ			champions[MAX_PLAYERS];
	t_cull			cull;
	t_champ			*victor;
	t_proc			*processes;
	t_uint			cycle;
	t_uint			dcycle;
	t_byte			nplayers;
	t_bool			gui : 1;
}					t_core;
#endif
