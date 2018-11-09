/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_gui_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 22:31:03 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/08 22:32:59 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_gui.h"


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

