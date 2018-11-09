/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 22:32:23 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/09 04:42:52 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "corewar.h"

int	gui_clean_up(t_gui *g)
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

int	gui_fatal_error(t_gui *g, char *msg)
{
	if (g != NULL)
		gui_clean_up(g);
	ft_printf(CONSOLE_TEXT_RED, "ERROR:", CONSOLE_TEXT_EOC, " %s\n", msg);
	exit(0);
	return (0);
}

int	gui_create_images(t_gui *g)
{
	if (g->img != NULL)
		(void)mlx_destroy_image(g->mlx, g->img);
	if ((g->img = mlx_new_image(g->mlx,
					WIN_TOTAL_WIDTH, WIN_TOTAL_HEIGHT)) == NULL)
		(void)gui_fatal_error(g, "mlx_new_image() failed");
	g->img_data = mlx_get_data_addr(g->img,
			&g->img_bpp, &g->img_size, &g->img_endian);
	return (0);
}

int	gui_init(t_core *core)
{
	t_gui	*g;

	g = ft_memalloc(sizeof(t_gui));
	g->core = core;
	if ((g->mlx = mlx_init()) == NULL)
		gui_fatal_error(g, "mlx_init() failed");
	(void)mlx_do_key_autorepeaton(g->mlx);
	g->win = mlx_new_window(g->mlx,
			WIN_TOTAL_WIDTH, WIN_TOTAL_HEIGHT, WIN_BLOCK_TITLE);
	if (g->win == NULL)
		gui_fatal_error(g, "mlx_new_window() failed");
	g->cpf = 1;
	(void)gui_init_colors(g);
	(void)mlx_hook(g->win, KEYPRESS, KEYPRESSMASK, gui_key_repeat, g);
	(void)mlx_key_hook(g->win, gui_key_hook, g);
	(void)mlx_mouse_hook(g->win, gui_mouse_hook, g);
	(void)mlx_expose_hook(g->win, gui_expose_hook, g);
	(void)mlx_loop_hook(g->mlx, GUI_LOOP_HOOK, g);
	(void)mlx_loop(g->mlx);
	(void)gui_clean_up(g);
	return (0);
}
