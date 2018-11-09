/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_functions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:14:46 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/08 22:28:40 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_FUNCTIONS_H
# define GUI_FUNCTIONS_H

#include "corewar_gui.h"

typedef struct s_corewar_gui	t_corewar_gui;

int	corewar_gui_block_visuals(t_corewar_gui *g);
int	corewar_gui_calc_fps(t_corewar_gui *g);
int	corewar_gui_create_images(t_corewar_gui *g);
int	corewar_gui_dist_bar(t_corewar_gui *g);
int	corewar_gui_dist_bar_color(t_corewar_gui *g, int pos);
int	corewar_gui_expose_hook(t_corewar_gui *g);
int	corewar_gui_get_block_color(t_corewar_gui *g, int i, int j);
int	corewar_gui_hsl2rgb(float h, float s, float l);
int	corewar_gui_increment_cpf(int keycode, t_corewar_gui *g);
int	corewar_gui_info_panel(t_corewar_gui *g);
int	corewar_gui_init_colors(t_corewar_gui *g);
int	corewar_gui_is_numeric_key(int keycode);
int	corewar_gui_key_hook(int keycode, t_corewar_gui *g);
int	corewar_gui_key_repeat(int keycode, t_corewar_gui *g);
int	corewar_gui_live_bar(t_corewar_gui *g);
int	corewar_gui_live_bar_color(t_corewar_gui *g, int j);
int	corewar_gui_live_bar_prepare_values(t_corewar_gui *g, float *percent);
int	corewar_gui_loop_hook(t_corewar_gui *g);
int	corewar_gui_mark_pc(t_corewar_gui *g, int i, int j);
int	corewar_gui_mouse_hook(int button, int x, int y, t_corewar_gui *g);
int	corewar_gui_pc_boxes(t_corewar_gui *g);
int	corewar_gui_put_block(t_corewar_gui *g, int i, int j);
int	corewar_gui_set_cpf_to_numeric_key(int keycode, t_corewar_gui *g);
int	gui_hsl2rgb_hue_index(float h1);
int	gui_hsl2rgb_int(float *rgb);
int	gui_hsl2rgb_values(float *rgb, float *cxo, float m, int i);
void	corewar_gui_clean_up(t_corewar_gui *g);
void	corewar_gui_fatal_error(t_corewar_gui *g, char *msg);
void	corewar_gui_init(t_core *core);

#endif
