/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_gui_live_bar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 01:06:49 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/08 22:24:13 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_gui.h"

int	corewar_gui_live_bar_prepare_values(t_corewar_gui *g, float *percent)
{
	float	one_percent;
	float	plives;
	int		i;

	i = 0;
	one_percent = (float)g->core->cull.plives / (float)100;
	while (i < MAX_PLAYERS)
	{
		percent[i] = 0;
		if (g->core->champions[i].plives > 0)
		{
			plives = (float)g->core->champions[i].plives;
			percent[i] = (float)plives / (float)one_percent;
		}
		i++;
	}
	return (0);
}

int	corewar_gui_live_bar_color(t_corewar_gui *g, int j)
{
	float	position;
	float	percent[MAX_PLAYERS];
	float	sum;
	int		i;

	if (g->core->cull.plives == 0)
		return (g->player_colors[0][MAX_LUM_STEPS / LUM_TEXT_DIV]);
	(void)corewar_gui_live_bar_prepare_values(g, &percent[0]);
	i = 0;
	sum = 0;
	position = (float)j / ((float)LIVE_BAR_WIDTH / (float)100);
	while (i < MAX_PLAYERS)
	{
		sum += percent[i];
		if (position <= sum)
			return (g->player_colors[i + 1][MAX_LUM_STEPS / LUM_TEXT_DIV]);
		i++;
	}
	return (LIVE_BAR_DEFAULT_COLOR);
}

int	corewar_gui_live_bar(t_corewar_gui *g)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	*ptr;

	i = LIVE_BAR_X_POS;
	x = i + LIVE_BAR_HEIGHT;
	while (i < x)
	{
		j = LIVE_BAR_Y_POS;
		y = j + LIVE_BAR_WIDTH;
		while (j < y)
		{
			ptr = (int *)&g->img_data[(i * WTW + j) * g->img_bpp / CHAR_BIT];
			if ((i == LBXP) || (i == x - 1) || (j == LBYP) || (j == y - 1))
				*ptr = LIVE_BAR_BORDER_COLOR;
			else
				*ptr = corewar_gui_live_bar_color(g, j - LIVE_BAR_Y_POS);
			j++;
		}
		i++;
	}
	return (0);
}

int	corewar_gui_dist_bar_color(t_corewar_gui *g, int pos)
{
	int i;
	int left;
	int right;

	i = 1;
	left = 0;
	right = 0;
	pos *= MEM_SIZE / DIST_WIDTH;
	while (i < MAX_PLAYERS + 1)
	{
		right = g->distrib[i];
		right += left;
		if ((pos >= left) && (pos < right))
			return (g->player_colors[i][MAX_LUM_STEPS / LUM_TEXT_DIV]);
		left = right;
		i++;
	}
	right += g->distrib[0];
	if ((pos >= left) && (pos <= right))
		return (g->player_colors[0][0]);
	return (DISTRIB_DEFAULT_COLOR);
}

int	corewar_gui_dist_bar(t_corewar_gui *g)
{
	int	i;
	int x;
	int	j;
	int y;
	int	*ptr;

	i = DIST_X_POS;
	x = i + DIST_HEIGHT;
	while (i < x)
	{
		j = DIST_Y_POS;
		y = j + DIST_WIDTH;
		while (j < y)
		{
			ptr = (int *)&g->img_data[(i * WTW + j) * g->img_bpp / CHAR_BIT];
			if ((i == DXP) || (i == x - 1) || (j == DYP) || (j == y - 1))
				*ptr = DIST_BORDER_COLOR;
			else
				*ptr = corewar_gui_dist_bar_color(g, j - DIST_Y_POS);
			j++;
		}
		i++;
	}
	return (0);
}
