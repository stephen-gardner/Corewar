/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_gui.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 03:06:53 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/08 20:35:09 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_gui.h"
#include "corewar.h"


void	corewar_gui_clean_up(t_corewar_gui *g)
{
	if (g == NULL)
		return ;
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
	return ;
}

void	corewar_gui_fatal_error(t_corewar_gui *g, char *msg)
{
	if (g != NULL)
		corewar_gui_clean_up(g);
	ft_printf(CONSOLE_TEXT_RED, "ERROR:", CONSOLE_TEXT_EOC, " %s\n", msg);
	exit(0);
}




int	corewar_gui_info_panel(t_corewar_gui *g)
{
	char	text[COMMENT_LENGTH + 1];
	char	*s;
	int		i;
	int		x;
	int		y;
	int		c;

	y = INFO_PANEL_Y + 10;
	x = INFO_PANEL_X;
	c = INFO_TEXT_COLOR;

	g->state == 1 ? (s = STATE_RUNNING) : (s = STATE_PAUSED);
	mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, c, s); x += GUI_CHAR_HEIGHT;
	s = (char *)&text;
	ft_sprintf(s, FPS_STR, g->fps, g->cpf, g->fps * g->cpf);
	mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, c, s); x += GUI_CHAR_HEIGHT * 3;

	ft_sprintf(s, PROC_NUM, g->nprocesses);
	mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, c, s); x += GUI_CHAR_HEIGHT;
	ft_sprintf(s, CYCLE_NUM, g->core->cycle);
	mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, c, s); x += GUI_CHAR_HEIGHT * 2;


	ft_sprintf(s, CYCLE_TO_DIE_STR, g->core->cull.ctd);
	mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, c, s); x += GUI_CHAR_HEIGHT;
	ft_sprintf(s, CYCLE_DELTA_STR, CYCLE_DELTA);
	mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, c, s); x += GUI_CHAR_HEIGHT * 2;
	ft_sprintf(s, NBR_LIVE_STR, g->core->cull.nbr_lives, NBR_LIVE);
	mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, c, s); x += GUI_CHAR_HEIGHT;
	ft_sprintf(s, MAX_CHECKS_STR, g->core->cull.checks, MAX_CHECKS);
	mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, c, s); x += GUI_CHAR_HEIGHT;


	i = 0;
	x += GUI_CHAR_HEIGHT * 2;
	while (i < g->core->nplayers)
	{
		ft_sprintf(s, PLAYER_NUM, i, g->core->champions[i].id);
		mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, c, s); x += GUI_CHAR_HEIGHT;
		ft_sprintf(s, GUI_STRING, MSL, g->core->champions[i].name);
		mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, g->player_colors[i + 1][0], s); x += GCH;

		ft_sprintf(s, LAST_LIVE_STR, g->core->champions[i].last_live);
		mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, c, s); x += GCH;
		ft_sprintf(s, LIVES_IN_PERIOD_STR, g->core->champions[i].plives);
		mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, c, s); x += GCH * 2;
		i++;
	}

//end of the game, print winner name
	if (g->core->processes == 0)
	{
		i = 0;
		x += GUI_CHAR_HEIGHT;
		while (i < MAX_PLAYERS)
		{
			if (g->core->victor == &g->core->champions[i])
			{
				mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, c, GUI_WINNER1);	x+= GUI_CHAR_HEIGHT;
				ft_sprintf(s, GUI_STRING, MSL, g->core->victor->name);
				mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, g->player_colors[i + 1][0], s); x += GCH;
//				mlx_string_put_to_image(g->mlx, g->win, g->img, y, x, g->player_colors[i + 1][0], g->core->victor->name);
//				x += GUI_CHAR_HEIGHT;
				sprintf(s, GUI_COMMENT_QUOTES, MSL - 3, g->core->victor->comment);
				text[46] = 0;
				mlx_string_put_to_image(g->mlx, g->win, g->img, PLAYER_Y, x, g->player_colors[i + 1][0], s);	x+= GUI_CHAR_HEIGHT;
				break ;		
			}
			i++;
		}
	}


	mlx_string_put_to_image(g->mlx, g->win, g->img, LIVE_BAR_TEXT_Y_POS, LIVE_BAR_TEXT_X_POS, INFO_TEXT_COLOR, LIVE_BAR_TEXT_STR);
	mlx_string_put_to_image(g->mlx, g->win, g->img, DIST_TEXT_Y_POS, DIST_TEXT_X_POS, INFO_TEXT_COLOR, DIST_TEXT);
	return (0);
}

int	corewar_gui_create_images(t_corewar_gui *g)
{
	if (g->img != NULL)
		(void)mlx_destroy_image(g->mlx, g->img);
	if ((g->img = mlx_new_image(g->mlx, WIN_TOTAL_WIDTH, WIN_TOTAL_HEIGHT))== NULL)
		(void)corewar_gui_fatal_error(g, "mlx_new_image() failed");
	g->img_data = mlx_get_data_addr(g->img, &g->img_bpp, &g->img_size, &g->img_endian);
	return (0);
}
//----------------------------------------------------------------------------------------------

int	corewar_gui_get_distrib_color(t_corewar_gui *g, int j)
{
	float x = DIST_WIDTH;
	x = (float)MEM_SIZE / (float)DIST_WIDTH;
	float y = (float)j * (float)x;
	int	i = 1;
	int	left = 0;
	int right = 0;
	while (i < MAX_PLAYERS + 1)
	{
		right = g->distrib[i];
		right += left;
		if (((int)y >= left) && ((int)y <= right))
			return (g->player_colors[i][MAX_LUM_STEPS / LUM_TEXT_DIV]);
		left = right;
		i++;
	}
	right += g->distrib[0];
	if (((int)y >= left) && ((int)y <= right))
		return (g->player_colors[0][0]);
	return (DISTRIB_DEFAULT_COLOR);
}

int	corewar_gui_fill_distrib(t_corewar_gui *g)
{
	int	i;
	int	j;
	int	*ptr;

	i = DIST_X_POS;
	while (i < DIST_HEIGHT + DIST_X_POS)
	{
		j = DIST_Y_POS;
		while (j < DIST_WIDTH + DIST_Y_POS)
		{
			ptr = (int *)&g->img_data[(i * WIN_TOTAL_WIDTH * (g->img_bpp/CHAR_BIT)) + (j * (g->img_bpp/CHAR_BIT))];

			if ((i == DIST_X_POS) || (i == DIST_X_POS + DIST_HEIGHT - 1) || (j == DIST_Y_POS) || (j == DIST_Y_POS + DIST_WIDTH - 1))
				*ptr = DIST_BORDER_COLOR;
			else
				*ptr = corewar_gui_get_distrib_color(g, j - DIST_Y_POS);
			j++;
		}
		i++;
	}
	return (0);
}
//----------------------------------------------------------------------------------------------
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
	(void)corewar_gui_lives_bar(g);
	(void)corewar_gui_fill_distrib(g);
	(void)corewar_gui_calc_fps(g);
	(void)mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	(void)corewar_gui_info_panel(g);
	return (0);
}

void	corewar_gui_init(t_core *core)
{
	t_corewar_gui	*g;
	g = ft_memalloc(sizeof(t_corewar_gui));
	g->core = core;
	if ((g->mlx = mlx_init()) == NULL)
		corewar_gui_fatal_error(g, "mlx_init() failed");
	(void)mlx_do_key_autorepeaton(g->mlx);
	g->win = mlx_new_window(g->mlx, WIN_TOTAL_WIDTH, WIN_TOTAL_HEIGHT, WIN_BLOCK_TITLE);
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
	return ;
}
