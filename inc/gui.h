/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 03:08:18 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/09 02:12:39 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_GUI_H
# define COREWAR_GUI_H

#include "mlx.h"
# include "libft.h"
# include "ft_printf.h"
# include "keycode.h"
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include "corewar.h"
# include "gui_functions.h"

int      mlx_string_put_to_image(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y, int color, char *string);

# define BLOCK_DEFAULT_COLOR    0xbfbfbf	//grey, 75% lum
# define CONSOLE_TEXT_RED	"\033[0;31m"
# define CONSOLE_TEXT_EOC	"\033[0;00m"
# define COLOR_WHITE		0xffffff
# define COLOR_RED			0xff0000
# define COLOR_YELLOW		0xffff00
# define COLOR_GREEN		0x00ff00
# define COLOR_BLUE			0x0000ff
# define COLOR_MATRIX_GREEN	0x60b942
# define GUI_ARENA_SIZE		4096
# define KEYPRESSMASK		(1L<<0)
# define KEYPRESS			2
# define ABS2(n)				((n) > 0 ? (n) : -(n))
# define GUI_NUM_ROWS		64	//32, 16
# define GUI_NUM_COLS		64	//128, 256
# define GUI_CHAR_WIDTH		9
# define GUI_CHAR_HEIGHT	15
# define GCH				GUI_CHAR_HEIGHT
# define GUI_ROW_SPACING	0
# define GUI_COL_SPACING	4
# define GUI_ROW_HEIGHT		(GUI_CHAR_HEIGHT + GUI_ROW_SPACING)
# define GUI_COL_WIDTH		((GUI_CHAR_WIDTH * 2) + GUI_COL_SPACING)
# define GUI_ARENA_X_POS	10
# define GUI_ARENA_Y_POS	10
# define WIN_HEIGHT			((GUI_ROW_HEIGHT * GUI_NUM_ROWS) + (GUI_ARENA_X_POS * 2))
# define WIN_WIDTH			(((GUI_COL_WIDTH * GUI_NUM_COLS) - GUI_COL_SPACING) + (GUI_ARENA_Y_POS * 2))
# define WIN_TITLE			"corewar_gui @ 42"
# define GUI_BLOCK_NUM_ROWS		64	//32, 16
# define GUI_BLOCK_NUM_COLS		64	//128, 256
# define GBNC					GUI_BLOCK_NUM_COLS
# define GUI_BLOCK_WIDTH	10
# define GUI_BLOCK_HEIGHT	10
# define GUI_BLOCK_ROW_SPACING	1
# define GUI_BLOCK_COL_SPACING	1
# define GUI_BLOCK_ROW_HEIGHT		(GUI_BLOCK_HEIGHT + GUI_BLOCK_ROW_SPACING)
# define GUI_BLOCK_COL_WIDTH		(GUI_BLOCK_WIDTH + GUI_BLOCK_COL_SPACING)
# define GUI_BLOCK_ARENA_X_POS	10
# define GUI_BLOCK_ARENA_Y_POS	10
# define WIN_BLOCK_HEIGHT			((GUI_BLOCK_ROW_HEIGHT * GUI_BLOCK_NUM_ROWS) + (GUI_BLOCK_ARENA_X_POS * 2))
# define WIN_BLOCK_WIDTH			((GUI_BLOCK_COL_WIDTH * GUI_BLOCK_NUM_COLS) + (GUI_BLOCK_ARENA_Y_POS * 2))
# define WIN_BLOCK_TITLE			"corewar_gui [blocks] @ 42"
# define SZ_INT				sizeof(int)
# define INFO_PANEL_X_POS	GUI_BLOCK_ARENA_X_POS
# define INFO_PANEL_Y_POS	WIN_BLOCK_WIDTH
# define INFO_PANEL_WIDTH	(WIN_BLOCK_WIDTH / 2)
# define PANEL_H_SPACING		GUI_BLOCK_ARENA_X_POS
# define PANEL_V_SPACING		GUI_BLOCK_ARENA_Y_POS
# define WIN_TOTAL_WIDTH		(WIN_BLOCK_WIDTH + INFO_PANEL_WIDTH)
# define WTW WIN_TOTAL_WIDTH
# define WIN_TOTAL_HEIGHT	(WIN_BLOCK_HEIGHT)
# define BORDER_BOX_COLOR	0xffffff
# define MAX_LUM_STEPS	255
# define LUM_MAX_STEPS	MAX_LUM_STEPS
# define LUM_START			70	//brightest
# define LUM_END			30	//darkest
# define LUM_RANGE			(LUM_START - LUM_END)
# define CPF_MAX			20
# define LUM_TEXT_DIV	5
# define GUI_WINNER1 "game over! the winner is:"
# define GUI_COMMENT_QUOTES "\"%.*s\""
# define GUI_PC_MARK_SZ	2
# define INFO_PANEL_X	(GUI_BLOCK_ARENA_X_POS)
# define INFO_PANEL_Y	(WIN_BLOCK_WIDTH)
# define STATE_X			(INFO_PANEL_X + 10)
# define STATE_Y			(INFO_PANEL_Y + 10)
# define STATE_PAUSED	"game state: **paused**"
# define STATE_RUNNING	"game state: **running**"

# define PROC_NUM		"total processes: %lu"
# define PROC_NUM_X		(CPS_X + GUI_CHAR_HEIGHT * 2)
# define PROC_NUM_Y		(INFO_PANEL_Y + 10)
# define CYCLE_NUM		"cycle: %u"
# define CYCLE_NUM_X		(PROC_NUM_X + GUI_CHAR_HEIGHT)
# define CYCLE_NUM_Y		(INFO_PANEL_Y + 10)
# define PLAYER_NAME_STR	"name:"
# define PLAYER_ID_STR	"id: 0x%08x"
# define PLAYER_X		(CYCLE_NUM_X + GUI_CHAR_HEIGHT)
# define PLAYER_Y		(INFO_PANEL_Y + 10)
# define PLAYER_NUM		"player %d, id: 0x%08x"
# define INFO_TEXT_COLOR	COLOR_WHITE
# define GUI_CONTROLS_INFO "use [space] to start/pause execution; [0-9] keys and [+-] keys to adjust cycles per second; [q] to quit"
//-----------------------------------------------------------------------------
# define DIST_WIDTH	(INFO_PANEL_WIDTH - (GUI_BLOCK_ARENA_Y_POS * 3))
# define DIST_HEIGHT	(GUI_BLOCK_HEIGHT + 2)
# define DIST_Y_POS	(INFO_PANEL_Y_POS + GUI_BLOCK_ARENA_Y_POS)
# define DIST_X_POS	(WIN_BLOCK_HEIGHT - (GUI_CHAR_HEIGHT * 3))
# define DIST_BORDER_COLOR 0xffffff
# define DIST_TEXT_Y_POS	(INFO_PANEL_Y_POS + GUI_BLOCK_ARENA_Y_POS)
# define DIST_TEXT_X_POS	(DIST_X_POS - (GUI_CHAR_HEIGHT * 1) - 4)
# define DIST_TEXT		"arena distribution"
#define DXP	DIST_X_POS
#define DYP	DIST_Y_POS
//-----------------------------------------------------------------------------
#define LIVE_BAR_TEXT_STR "live breakdown for current period"
#define LIVE_BAR_TEXT_Y_POS	(INFO_PANEL_Y_POS + GUI_BLOCK_ARENA_Y_POS)
#define LIVE_BAR_TEXT_X_POS	(LIVE_BAR_X_POS - (GUI_CHAR_HEIGHT * 1) - 4)
#define LIVE_BAR_HEIGHT 	(GUI_BLOCK_HEIGHT + 2)
#define LIVE_BAR_WIDTH		(INFO_PANEL_WIDTH - (GUI_BLOCK_ARENA_Y_POS * 3))
#define LIVE_BAR_X_POS		(WIN_BLOCK_HEIGHT - (GUI_CHAR_HEIGHT * 6))
#define LIVE_BAR_Y_POS		(INFO_PANEL_Y_POS + GUI_BLOCK_ARENA_Y_POS)
#define LBXP	LIVE_BAR_X_POS
#define LBYP	LIVE_BAR_Y_POS
#define LIVE_BAR_BORDER_COLOR	0xffffff
#define LIVE_BAR_DEFAULT_COLOR	0xffffff
#define DISTRIB_DEFAULT_COLOR	0xffffff
//-----------------------------------------------------------------------------
#define CYCLE_TO_DIE_STR	"cycle to die: %u"
#define CYCLE_DELTA_STR		"cycle delta: %u"
#define NBR_LIVE_STR		"nbr_live: %u/%u"
#define MAX_CHECKS_STR		"max_checks: %u/%u"
#define LAST_LIVE_STR		"last live: %u"
#define	LIVES_IN_PERIOD_STR	"lives in current period: %d"
//-----------------------------------------------------------------------------
# define FPS_STR			"fps [%d] * cpf [%d] = cps [%d]"
# define FPS_X			(STATE_X + GUI_CHAR_HEIGHT * 2)
# define FPS_Y			(INFO_PANEL_Y + 10)
# define CPF_STR			"cycles per frame: %d"
# define CPF_X			(FPS_X + GUI_CHAR_HEIGHT)
# define CPF_Y			(INFO_PANEL_Y + 10)
# define CPS_STR			"cycles per second: %d"
# define CPS_X			(CPF_X + GUI_CHAR_HEIGHT)
# define CPS_Y			(INFO_PANEL_Y + 10)
//-----------------------------------------------------------------------------
# define GUI_PC_BOX_COLOR 0xffffff
# define INFO_PANEL_TEXT_MAX_LEN	(INFO_PANEL_WIDTH - (GUI_BLOCK_ARENA_Y_POS * 3))
# define IPTML INFO_PANEL_TEXT_MAX_LEN
# define MAX_STRING_LEN	(IPTML / (GUI_CHAR_WIDTH - 2))
# define MSL MAX_STRING_LEN
#define GUI_NUMERIC_KEY_ARRAY	{KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0}
#define GUI_NUMERIC_KEY_VALUES	{1, 2, 3, 4, 5, 6, 7, 8, 9, 0}
#define GUI_STRING "%.*s"
# define GFX_AGE_SPEED      10
#define GUI_PLAYER_HUES1 {0, 60, 120, 240}
#define GUI_PLAYER_HUES2 {120, 240, 0, 180}
#define GUI_HSL2RGB_MATRIX1 {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}}
#define GUI_HSL2RGB_MATRIX2	{{0,1,2}, {1,0,2}, {2,0,1}, {2,1,0}, {1,2,0}, {0,2,1}, {2,2,2}}
#define MLX_PUTS	mlx_string_put_to_image

typedef struct s_corewar_gui
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

} t_gui;


#endif
