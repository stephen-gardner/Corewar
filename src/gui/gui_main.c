/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_gui.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 22:32:23 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/08 23:00:05 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_gui.h"
#include "corewar.h"

int	corewar_gui_clean_up(t_corewar_gui *g)
{
	if (g == NULL)
		return (0);
	if (g->img != NULL)
	{
		(void)mlx_destroy_image(g->mlx, g->img);
		g->img = NULL;
	}
	if (g->win != NULL)
	{
		(void)mlx_destroy_window(g->mlx, g->win);
		g->win = NULL;
	}
	if (g->mlx != NULL)
	{
		free(g->mlx);
		g->mlx = NULL;
	}
	free(g);
	return (0);
}

int	corewar_gui_fatal_error(t_corewar_gui *g, char *msg)
{
	if (g != NULL)
		corewar_gui_clean_up(g);
	ft_printf(CONSOLE_TEXT_RED, "ERROR:", CONSOLE_TEXT_EOC, " %s\n", msg);
	exit(0);
	return (0);
}

int	corewar_gui_create_images(t_corewar_gui *g)
{
	if (g->img != NULL)
		(void)mlx_destroy_image(g->mlx, g->img);
	if ((g->img = mlx_new_image(g->mlx,
					WIN_TOTAL_WIDTH, WIN_TOTAL_HEIGHT)) == NULL)
		(void)corewar_gui_fatal_error(g, "mlx_new_image() failed");
	g->img_data = mlx_get_data_addr(g->img,
			&g->img_bpp, &g->img_size, &g->img_endian);
	return (0);
}

int	corewar_gui_loop_hook(t_corewar_gui *g)
{
	int	i;

	i = 0;
	while ((g->state == 1) && (i < g->cpf))
	{
		if (g->core->processes)
			execute_war(g->core);
		i++;
	}
	(void)corewar_gui_create_images(g);
	(void)corewar_gui_pc_boxes(g);
	(void)corewar_gui_block_visuals(g);
	(void)corewar_gui_live_bar(g);
	(void)corewar_gui_dist_bar(g);
	(void)corewar_gui_calc_fps(g);
	(void)corewar_gui_info_panel(g);
	(void)mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	(void)corewar_gui_info_panel(g);
	return (0);
}

int	corewar_gui_init(t_core *core)
{
	t_corewar_gui	*g;

	g = ft_memalloc(sizeof(t_corewar_gui));
	g->core = core;
	if ((g->mlx = mlx_init()) == NULL)
		corewar_gui_fatal_error(g, "mlx_init() failed");
	(void)mlx_do_key_autorepeaton(g->mlx);
	g->win = mlx_new_window(g->mlx,
			WIN_TOTAL_WIDTH, WIN_TOTAL_HEIGHT, WIN_BLOCK_TITLE);
	if (g->win == NULL)
		corewar_gui_fatal_error(g, "mlx_new_window() failed");
	g->cpf = 1;
	(void)corewar_gui_init_colors(g);
	(void)mlx_hook(g->win, KEYPRESS, KEYPRESSMASK, corewar_gui_key_repeat, g);
	(void)mlx_key_hook(g->win, corewar_gui_key_hook, g);
	(void)mlx_mouse_hook(g->win, corewar_gui_mouse_hook, g);
	(void)mlx_expose_hook(g->win, corewar_gui_expose_hook, g);
	(void)mlx_loop_hook(g->mlx, corewar_gui_loop_hook, g);
	(void)mlx_loop(g->mlx);
	(void)corewar_gui_clean_up(g);
	return (0);
}
