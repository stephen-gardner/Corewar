/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coredef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 01:22:46 by sgardner          #+#    #+#             */
/*   Updated: 2019/01/27 22:18:18 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREDEF_H
# define COREDEF_H

/*
** #############################################################################
** # CONFIGURATION - Not easily tuned--it is recommended to leave it alone!    #
** #############################################################################
*/

/*
** Core
** For performance (and implementation) reasons, MEM_SIZE must be a power of 2
*/

# define MEM_SIZE			4096
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)
# define MAX_PLAYERS		4
# define DUMP_LEN			64

/*
** Lives / Process Culling
*/

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10
# define CULL_PROC			(t_uint)-1

/*
** Champions
*/

# define PROG_NAME_LENGTH	128
# define COMMENT_LENGTH		2048
# define COREWAR_EXEC_MAGIC	0x00EA83F3

/*
** #############################################################################
** # UTILITY                                                                   #
** #############################################################################
*/

/*
** Registers
*/

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE
# define REG_NUMBER			16

/*
** Op parameter types
*/

# define T_R				1
# define T_I				2
# define T_D				4
# define NOP				&g_ops[g_ops_size - 1]

/*
** Core access
*/

# define CORE_POS(x)		((x) & (MEM_SIZE - 1))
# define REL_POS(x)			((x) % IDX_MOD)
# define IDX_POS(ar, pc, x)	((ar) + CORE_POS(((pc) - (ar)) + REL_POS(x)))
# define ABS_POS(ar, pc, x)	((ar) + CORE_POS(((pc) - (ar)) + (x)))

/*
** Other
*/

# define REV				ft_revbytes
# define ERR				error
# define MSG				notice
# define SYS_ERR			ERR(DEFAULT_ERR, strerror(errno))

/*
** #############################################################################
** # LANG IDS                                                                  #
** #############################################################################
*/

/*
** Error Messages
*/

enum	e_errmsg
{
	DEFAULT_ERR,
	BAD_IO,
	CHAMP_TOO_LARGE,
	CHAMP_TOO_SMALL,
	INVALID_HEADER,
	NO_PLAYERS,
	SIZE_MISMATCH,
	TOO_MANY_CHAMPS,
	NERRMSGS
};

/*
** Standard Messages
*/

enum	e_notices
{
	ANNOUNCE_WINNER,
	ANNOUNCE_WINNER_TEAM,
	ANNOUNCE_LIVE,
	ANNOUNCE_LOSERS,
	CHAMP_COMMENT,
	LAUNCH_GUI,
	WAR_OVER,
	NNOTICES
};
#endif
