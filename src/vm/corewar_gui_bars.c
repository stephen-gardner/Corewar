/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_gui_bars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 01:06:49 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/08 20:37:16 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_gui.h"

int	corewar_gui_live_bar_color(t_corewar_gui *g, int j)
{
	if (g->core->cull.plives == 0)
		return (g->player_colors[0][MAX_LUM_STEPS / LUM_TEXT_DIV]);


	float percent[MAX_PLAYERS];
	float one_percent = (float)g->core->cull.plives / (float)100;
	int i = 0;
	while (i < MAX_PLAYERS)
	{
		percent[i] = 0;
		if (g->core->champions[i].plives > 0)
		{
			percent[i] = (float)g->core->champions[i].plives / (float)one_percent;
		}
		i++;
	}
	float position = (float)j / ((float)LIVE_BAR_WIDTH / (float)100);

	i = 0;
	float sum = 0;
	while (i < MAX_PLAYERS)
	{
		sum += percent[i];
		if (position <= sum)
		{
			return (g->player_colors[i + 1][MAX_LUM_STEPS / LUM_TEXT_DIV]);
		}
		i++;
	}
	return (LIVE_BAR_DEFAULT_COLOR);
}

#define LBXP	LIVE_BAR_X_POS
#define LBYP	LIVE_BAR_Y_POS

int	corewar_gui_lives_bar(t_corewar_gui *g)
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
			ptr = (int *)&g->img_data[(i * g->img_size) + (j * (g->img_bpp / CHAR_BIT))];
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
