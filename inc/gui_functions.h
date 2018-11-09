/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_functions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:14:46 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/09 05:24:51 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_FUNCTIONS_H
# define GUI_FUNCTIONS_H

# include "gui.h"
# include "corestructs.h"

typedef struct s_corewar_gui	t_gui;

int	gui_block_visuals(t_gui *g);
int	gui_calc_fps(t_gui *g);
int	gui_clean_up(t_gui *g);
int	gui_create_images(t_gui *g);
int	gui_dist_bar(t_gui *g);
int	gui_dist_bar_color(t_gui *g, int pos);
int	gui_expose_hook(t_gui *g);
int	gui_fatal_error(t_gui *g, char *msg);
int	gui_get_block_color(t_gui *g, int i, int j);
int	gui_hsl2rgb(float h, float s, float l);
int	gui_hsl2rgb_hue_index(float h1);
int	gui_hsl2rgb_int(float *rgb);
int	gui_hsl2rgb_values(float *rgb, float *cxo, float m, int i);
int	gui_increment_cpf(int keycode, t_gui *g);
int	gui_info_panel(t_gui *g);
int	gui_init(t_core *core);
int	gui_init_colors(t_gui *g);
int	gui_is_numeric_key(int keycode);
int	gui_key_hook(int keycode, t_gui *g);
int	gui_key_repeat(int keycode, t_gui *g);
int	gui_live_bar(t_gui *g);
int	gui_live_bar_color(t_gui *g, int j);
int	gui_live_bar_prepare_values(t_gui *g, float *percent);
int	gui_loop_hook_generic(t_gui *g);
int	gui_loop_hook_linux(t_gui *g);
int	gui_loop_hook_macos(t_gui *g);
int	gui_mark_pc(t_gui *g, int i, int j);
int	gui_mouse_hook(int button, int x, int y, t_gui *g);
int	gui_pc_boxes(t_gui *g);
int	gui_put_block(t_gui *g, int i, int j);
int	gui_set_cpf_to_numeric_key(int keycode, t_gui *g);
int	gui_text_players(t_gui *g, int x, int y, char *s);
int	gui_text_stats(t_gui *g, int x, int y, char *s);
int	gui_text_winner(t_gui *g, int x, int y, char *s);
int	mlx_string_put_to_image(void *mlx_ptr, void *win_ptr, void *img_ptr,
		int x, int y, int color, char *string);

#endif
