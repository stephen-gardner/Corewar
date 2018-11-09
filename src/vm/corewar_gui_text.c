/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_gui_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 22:31:03 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/09 00:18:41 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_gui.h"

int	corewar_gui_text_winner(t_corewar_gui *g, int x, int y, char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0xffffff;
	while (i < MAX_PLAYERS)
	{
		if (g->core->victor == &g->core->champions[i])
		{
			MLX_PUTS(g->mlx, g->win, g->img, y, x, c, GUI_WINNER1);
			x += GUI_CHAR_HEIGHT;
			ft_sprintf(s, GUI_STRING, MSL, g->core->victor->name);
			MLX_PUTS(g->mlx,
					g->win, g->img, y, x, g->player_colors[i + 1][0], s);
			x += GUI_CHAR_HEIGHT;
			sprintf(s, GUI_COMMENT_QUOTES, MSL - 3, g->core->victor->comment);
			MLX_PUTS(g->mlx,
					g->win, g->img, y, x, g->player_colors[i + 1][0], s);
			break ;
		}
		i++;
	}
	return (0);
}

int	corewar_gui_text_stats(t_corewar_gui *g, int x, int y, char *s)
{
	int	c;

	c = INFO_TEXT_COLOR;
	ft_sprintf(s, FPS_STR, g->fps, g->cpf, g->fps * g->cpf);
	MLX_PUTS(g->mlx, g->win, g->img, y, x, c, s);
	x += GUI_CHAR_HEIGHT * 3;
	ft_sprintf(s, PROC_NUM, g->nprocesses);
	MLX_PUTS(g->mlx, g->win, g->img, y, x, c, s);
	x += GUI_CHAR_HEIGHT;
	ft_sprintf(s, CYCLE_NUM, g->core->cycle);
	MLX_PUTS(g->mlx, g->win, g->img, y, x, c, s);
	x += GUI_CHAR_HEIGHT * 2;
	ft_sprintf(s, CYCLE_TO_DIE_STR, g->core->cull.ctd);
	MLX_PUTS(g->mlx, g->win, g->img, y, x, c, s);
	x += GUI_CHAR_HEIGHT;
	ft_sprintf(s, CYCLE_DELTA_STR, CYCLE_DELTA);
	MLX_PUTS(g->mlx, g->win, g->img, y, x, c, s);
	x += GUI_CHAR_HEIGHT * 2;
	ft_sprintf(s, NBR_LIVE_STR, g->core->cull.nbr_lives, NBR_LIVE);
	MLX_PUTS(g->mlx, g->win, g->img, y, x, c, s);
	x += GUI_CHAR_HEIGHT;
	ft_sprintf(s, MAX_CHECKS_STR, g->core->cull.checks, MAX_CHECKS);
	MLX_PUTS(g->mlx, g->win, g->img, y, x, c, s);
	return (x + GUI_CHAR_HEIGHT * 3);
}

int	corewar_gui_text_players(t_corewar_gui *g, int x, int y, char *s)
{
	int	i;
	int	c;

	i = 0;
	c = INFO_TEXT_COLOR;
	while (i < g->core->nplayers)
	{
		ft_sprintf(s, PLAYER_NUM, i, g->core->champions[i].id);
		MLX_PUTS(g->mlx, g->win, g->img, y, x, c, s);
		x += GUI_CHAR_HEIGHT;
		ft_sprintf(s, GUI_STRING, MSL, g->core->champions[i].name);
		MLX_PUTS(g->mlx, g->win, g->img, y, x, g->player_colors[i + 1][0], s);
		x += GUI_CHAR_HEIGHT;
		ft_sprintf(s, LAST_LIVE_STR, g->core->champions[i].last_live);
		MLX_PUTS(g->mlx, g->win, g->img, y, x, c, s);
		x += GUI_CHAR_HEIGHT;
		ft_sprintf(s, LIVES_IN_PERIOD_STR, g->core->champions[i].plives);
		MLX_PUTS(g->mlx, g->win, g->img, y, x, c, s);
		x += GUI_CHAR_HEIGHT * 2;
		i++;
	}
	return (x + GUI_CHAR_HEIGHT);
}

int	corewar_gui_info_panel(t_corewar_gui *g)
{
	char	text[COMMENT_LENGTH + 1];
	int		x;
	int		y;

	y = INFO_PANEL_Y + 10;
	x = INFO_PANEL_X;
	if (g->state == 1)
		MLX_PUTS(g->mlx, g->win, g->img, y, x, INFO_TEXT_COLOR, STATE_RUNNING);
	else
		MLX_PUTS(g->mlx, g->win, g->img, y, x, INFO_TEXT_COLOR, STATE_PAUSED);
	x += GUI_CHAR_HEIGHT;
	x = corewar_gui_text_stats(g, x, y, &text[0]);
	x = corewar_gui_text_players(g, x, y, &text[0]);
	if (g->core->processes == 0)
		(void)corewar_gui_text_winner(g, x, y, &text[0]);
	MLX_PUTS(g->mlx, g->win, g->img, LIVE_BAR_TEXT_Y_POS,
			LIVE_BAR_TEXT_X_POS, INFO_TEXT_COLOR, LIVE_BAR_TEXT_STR);
	MLX_PUTS(g->mlx, g->win, g->img, DIST_TEXT_Y_POS,
			DIST_TEXT_X_POS, INFO_TEXT_COLOR, DIST_TEXT);
	return (0);
}
