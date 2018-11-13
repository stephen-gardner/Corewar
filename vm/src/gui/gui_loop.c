/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 04:36:04 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/09 04:46:30 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/*
** on linux we have to call gui_info_panel() before mlx_put_image_to_window()
** on macos, its first mlx_put_image_to_window(), then gui_info_panel()
** the generic solution should work for both
*/

int	gui_loop_hook_linux(t_gui *g)
{
	int	i;

	i = 0;
	while ((g->state == 1) && (i < g->cpf))
	{
		if (g->core->processes)
			execute_war(g->core);
		i++;
	}
	(void)gui_create_images(g);
	(void)gui_pc_boxes(g);
	(void)gui_block_visuals(g);
	(void)gui_live_bar(g);
	(void)gui_dist_bar(g);
	(void)gui_calc_fps(g);
	(void)gui_info_panel(g);
	(void)mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	return (0);
}

int	gui_loop_hook_macos(t_gui *g)
{
	int	i;

	i = 0;
	while ((g->state == 1) && (i < g->cpf))
	{
		if (g->core->processes)
			execute_war(g->core);
		i++;
	}
	(void)gui_create_images(g);
	(void)gui_pc_boxes(g);
	(void)gui_block_visuals(g);
	(void)gui_live_bar(g);
	(void)gui_dist_bar(g);
	(void)gui_calc_fps(g);
	(void)mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	(void)gui_info_panel(g);
	return (0);
}

int	gui_loop_hook_generic(t_gui *g)
{
	int	i;

	i = 0;
	while ((g->state == 1) && (i < g->cpf))
	{
		if (g->core->processes)
			execute_war(g->core);
		i++;
	}
	(void)gui_create_images(g);
	(void)gui_pc_boxes(g);
	(void)gui_block_visuals(g);
	(void)gui_live_bar(g);
	(void)gui_dist_bar(g);
	(void)gui_calc_fps(g);
	(void)gui_info_panel(g);
	(void)mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	(void)gui_info_panel(g);
	return (0);
}
