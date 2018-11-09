/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 05:12:57 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/09 07:28:58 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "gui_functions.h"
# include "mlx.h"
# include "corewar.h"
# include "corestructs.h"
# include "libft.h"
# include "ft_printf.h"
# include "keycode.h"
# include <stdlib.h>
# include <limits.h>

# define CONSOLE_TEXT_RED		"\033[0;31m"
# define CONSOLE_TEXT_EOC		"\033[0;00m"

# define GFX_AGE_SPEED			10
# define CPF_MAX				20
# define GUI_ARENA_SIZE			4096

# define BLOCK_DEFAULT_COLOR    0xbfbfbf
# define GUI_PC_BOX_COLOR		0xffffff
# define LIVE_BAR_BORDER_COLOR	0xffffff
# define DIST_BORDER_COLOR		0xffffff
# define INFO_TEXT_COLOR		0xffffff
# define DISTRIB_DEFAULT_COLOR	BLOCK_DEFAULT_COLOR
# define LIVE_BAR_DEFAULT_COLOR	BLOCK_DEFAULT_COLOR

# define GUI_BLOCK_ROW_SPACING	1
# define GUI_BLOCK_COL_SPACING	1
# define GUI_BLOCK_ARENA_X_POS	10
# define GUI_BLOCK_ARENA_Y_POS	10
# define GUI_BLOCK_NUM_ROWS		64
# define GUI_BLOCK_NUM_COLS		64
# define GUI_BLOCK_WIDTH		10
# define GUI_BLOCK_HEIGHT		10
# define GUI_BLOCK_ROW_HEIGHT	(GUI_BLOCK_HEIGHT + GUI_BLOCK_ROW_SPACING)
# define GUI_BLOCK_COL_WIDTH	(GUI_BLOCK_WIDTH + GUI_BLOCK_COL_SPACING)
# define WIN_BLOCK_HEIGHT	((GBRH * GBNR) + (GUI_BLOCK_ARENA_X_POS * 2))

# define GBRH					GUI_BLOCK_ROW_HEIGHT
# define GBNC					GUI_BLOCK_NUM_COLS
# define GBNR					GUI_BLOCK_NUM_ROWS
# define GBCW					GUI_BLOCK_COL_WIDTH
# define WTW					WIN_TOTAL_WIDTH
# define GBNC					GUI_BLOCK_NUM_COLS
# define LBXP					LIVE_BAR_X_POS
# define LBYP					LIVE_BAR_Y_POS
# define DXP					DIST_X_POS
# define DYP					DIST_Y_POS
# define MSL					MAX_STRING_LEN

# define WIN_BLOCK_WIDTH		((GBCW * GBNC) + (GUI_BLOCK_ARENA_Y_POS * 2))
# define WIN_TOTAL_WIDTH		(WIN_BLOCK_WIDTH + INFO_PANEL_WIDTH)
# define WIN_TOTAL_HEIGHT		(WIN_BLOCK_HEIGHT)

# define MAX_LUM_STEPS			255
# define LUM_START				70
# define LUM_END				30
# define LUM_TEXT_DIV			5
# define LUM_RANGE				(LUM_START - LUM_END)
# define LUM_MAX_STEPS			MAX_LUM_STEPS

# define GUI_PLAYER_HUES1		{0, 60, 120, 240}
# define GUI_PLAYER_HUES2		{120, 240, 0, 180}
# define GUI_HSL2RGB_MATRIX1	{{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}}
# define HSL_M1 {{0,1,2}, {1,0,2}, {2,0,1}, {2,1,0}, {1,2,0}, {0,2,1}, {2,2,2}}
# define GUI_HSL2RGB_MATRIX2	HSL_M1

# define LIVE_BAR_TEXT_Y_POS	(INFO_PANEL_Y_POS + GUI_BLOCK_ARENA_Y_POS)
# define LIVE_BAR_HEIGHT 		(GUI_BLOCK_HEIGHT + 2)
# define LIVE_BAR_WIDTH			(INFO_PANEL_WIDTH - (GUI_BLOCK_ARENA_Y_POS * 3))
# define LIVE_BAR_X_POS			(WIN_BLOCK_HEIGHT - (GUI_CHAR_HEIGHT * 6))
# define LIVE_BAR_Y_POS			(INFO_PANEL_Y_POS + GUI_BLOCK_ARENA_Y_POS)

# define DIST_TEXT_Y_POS		(INFO_PANEL_Y_POS + GUI_BLOCK_ARENA_Y_POS)
# define DIST_WIDTH				(INFO_PANEL_WIDTH - (GUI_BLOCK_ARENA_Y_POS * 3))
# define DIST_HEIGHT			(GUI_BLOCK_HEIGHT + 2)
# define DIST_Y_POS				(INFO_PANEL_Y_POS + GUI_BLOCK_ARENA_Y_POS)
# define DIST_X_POS				(WIN_BLOCK_HEIGHT - (GUI_CHAR_HEIGHT * 3))

# define KEYPRESSMASK			(1L<<0)
# define KEYPRESS				2
# define GUI_NUMERIC_KEY_ARRAY	GNKA
# define GNKA {KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9, KEY_0}
# define GUI_NUMERIC_KEY_VALUES	{1, 2, 3, 4, 5, 6, 7, 8, 9, 0}

# define INFO_PANEL_WIDTH		(WIN_BLOCK_WIDTH / 2)
# define INFO_PANEL_Y_POS		WIN_BLOCK_WIDTH

# define INFO_PANEL_Y			(WIN_BLOCK_WIDTH)
# define INFO_PANEL_TEXT_MAX_LEN (INFO_PANEL_WIDTH - (GUI_BLOCK_ARENA_Y_POS*3))
# define IPTML INFO_PANEL_TEXT_MAX_LEN
# define MAX_STRING_LEN			(IPTML / (GUI_CHAR_WIDTH - 2))

# define WIN_BLOCK_TITLE		"corewar @ 42"
# define DIST_TEXT				"arena distribution"
# define LIVE_BAR_TEXT_STR		"live breakdown for current period"
# define STATE_PAUSED			"game state: **paused**"
# define STATE_RUNNING			"game state: **running**"
# define FPS_STR				"fps [%d] * cpf [%d] = cps [%d]"
# define PLAYER_NUM				"player %d, id: 0x%08x"
# define CYCLE_NUM				"cycle: %u"
# define PROC_NUM				"total processes: %lu"
# define GUI_CONTROLS_INFO		GCI_1 GCI_2 GCI_3
# define GCI_1 "use [space] to start/pause execution; "
# define GCI_2 "[0-9] keys and [+-] keys to adjust cycles per second; "
# define GCI_3 "[q] to quit"
# define CYCLE_TO_DIE_STR		"cycle to die: %u"
# define CYCLE_DELTA_STR		"cycle delta: %u"
# define NBR_LIVE_STR			"nbr_live: %u/%u"
# define MAX_CHECKS_STR			"max_checks: %u/%u"
# define LAST_LIVE_STR			"last live: %u"
# define LIVES_IN_PERIOD_STR	"lives in current period: %d"
# define GUI_WINNER1			"game over! the winner is:"
# define GUI_COMMENT_QUOTES		"\"%.*s\""
# define GUI_STRING				"%.*s"

# define MLX_PUTS	mlx_string_put_to_image

# define CHAR_BIT __CHAR_BIT__

# if __linux__
#  define GUI_CHAR_HEIGHT		15
#  define GUI_CHAR_WIDTH		9
#  define LIVE_BAR_TEXT_X_POS	LIVE_BAR_X_POS - (GUI_CHAR_HEIGHT * 1) + 7
#  define DIST_TEXT_X_POS		DIST_X_POS - (GUI_CHAR_HEIGHT * 1) + 7
#  define GUI_LOOP_HOOK	gui_loop_hook_linux
#  define INFO_PANEL_X			(GUI_BLOCK_ARENA_X_POS + 10)
# elif __APPLE__
#  define GUI_CHAR_HEIGHT		15
#  define GUI_CHAR_WIDTH		9
#  define LIVE_BAR_TEXT_X_POS	(LIVE_BAR_X_POS - (GUI_CHAR_HEIGHT * 1) - 4)
#  define DIST_TEXT_X_POS		(DIST_X_POS - (GUI_CHAR_HEIGHT * 1) - 4)
#  define INFO_PANEL_X			(GUI_BLOCK_ARENA_X_POS)
#  define GUI_LOOP_HOOK	gui_loop_hook_macos
# else
#  define GUI_CHAR_HEIGHT		15
#  define GUI_CHAR_WIDTH		9
#  define LIVE_BAR_TEXT_X_POS	LIVE_BAR_X_POS - (GUI_CHAR_HEIGHT * 1) + 7
#  define DIST_TEXT_X_POS		DIST_X_POS - (GUI_CHAR_HEIGHT * 1) + 7
#  define INFO_PANEL_X			(GUI_BLOCK_ARENA_X_POS + 10)
#  define GUI_LOOP_HOOK	gui_loop_hook_generic
# endif

typedef struct		s_corewar_gui
{
	t_core			*core;
	void			*mlx;
	void			*win;
	void			*img;
	int				img_bpp;
	int				img_size;
	int				img_endian;
	char			*img_data;
	int				state;
	int				fps;
	int				cpf;
	unsigned long	nprocesses;
	char			pc_box[MEM_SIZE];
	int				player_colors[MAX_PLAYERS + 1][MAX_LUM_STEPS + 1];
	int				distrib[MAX_PLAYERS + 1];
	void			*img_dist;
	int				img_dist_bpp;
	int				img_dist_sz;
	int				img_dist_endian;
	char			*img_dist_data;
}					t_gui;

#endif
