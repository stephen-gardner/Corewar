/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_gui.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 03:08:18 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/01 09:51:58 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_GUI_H
# define COREWAR_GUI_H

# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"
# include "keycode.h"
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include "corewar.h"

#define BLOCK_DEFAULT_COLOR		0xbfbfbf	//grey, 75% lum
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
# define GUI_CHAR_WIDTH		10
# define GUI_CHAR_HEIGHT	20
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
# define WIN_TOTAL_HEIGHT	(WIN_BLOCK_HEIGHT)
# define BORDER_BOX_COLOR	0xffffff
# define MAX_LUM_STEPS	255
# define LUM_MAX_STEPS	MAX_LUM_STEPS
# define LUM_START			70	//brightest
# define LUM_END			30	//darkest
# define LUM_RANGE			(LUM_START - LUM_END)
# define CPF_MAX			20
# define LUM_TEXT_DIV	5



typedef	struct	s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			color;
}				t_line;

typedef struct s_corewar_gui
{
	t_core			*core;
	void			*mlx;
	void			*win;
	void			*img;
	int				img_bpp;
	int				img_sz;
	int				img_endian;
	char			*img_data;
	int				state;	// 0 = paused, 1 = running
	int				fps;
	int				cpf;
	unsigned long	nproc;
	char			pc_box[MEM_SIZE];
//	unsigned char	*arena;
//	int				owner[GUI_ARENA_SIZE];
//	int				age[GUI_ARENA_SIZE];
//	int				*colors;
	int				p_colors[MAX_PLAYERS + 1][MAX_LUM_STEPS];
	int				distrib[MAX_PLAYERS + 1];
	void			*img_dist;
	int				img_dist_bpp;
	int				img_dist_sz;
	int				img_dist_endian;
	char			*img_dist_data;

} t_corewar_gui;


void	corewar_gui_clean_up(t_corewar_gui *g);
void	corewar_gui_fatal_error(t_corewar_gui *g, char *msg);
void	corewar_gui_init(t_core *core);
void	corewar_gui_make_pcolors(t_corewar_gui *g);
void	corewar_gui_random_age(t_corewar_gui *g);
void	corewar_gui_random_fill_arena(t_corewar_gui *g);
void	corewar_gui_set_owner(t_corewar_gui *g);
void	plot_line(t_corewar_gui *g, t_line line);
void	plot_line_high(t_corewar_gui *g, t_line line, int dx, int dy);
void	plot_line_low(t_corewar_gui *g, t_line line, int dx, int dy);
void	plot_mini_calc(int *i1, int *i2, int *i3, int *i4);
void	plot_swap_coords(t_line *line);
int	corewar_gui_block_visuals(t_corewar_gui *g);
int	corewar_gui_border_box(t_corewar_gui *g);
int	corewar_gui_char_visuals(t_corewar_gui *g);
int	corewar_gui_expose_hook(t_corewar_gui *g);
int	corewar_gui_get_color(t_corewar_gui *g, int i, int j);
int	corewar_gui_info_panel(t_corewar_gui *g);
int	corewar_gui_init_colors(t_corewar_gui *g);
int	corewar_gui_key_hook(int keycode, t_corewar_gui *g);
int	corewar_gui_key_repeat(int keycode, t_corewar_gui *fdf);
int	corewar_gui_loop_hook(t_corewar_gui *g);
int	corewar_gui_mouse_hook(int button, int x, int y, t_corewar_gui *g);
int	corewar_gui_put_block(t_corewar_gui *g, int i, int j);
int	hsl_to_rgb(float h, float s, float l);
int	make_color_array(t_corewar_gui *g, float initial_hue);



#endif
