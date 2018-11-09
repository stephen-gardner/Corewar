/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 21:09:55 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/09 02:08:36 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include <math.h>

/*
** this will convert 3 floats (r, g, b) with range [0..1] to an int
** for [0, 1, 1] function will return 0x00ffff
** for [1, 0, 1] function will return 0xff00ff
*/

int	gui_hsl2rgb_int(float *rgb)
{
	unsigned char ri;
	unsigned char gi;
	unsigned char bi;

	ri = roundf(UCHAR_MAX * rgb[0]);
	gi = roundf(UCHAR_MAX * rgb[1]);
	bi = roundf(UCHAR_MAX * rgb[2]);
	return ((ri << 16) + (gi << 8) + bi);
}

int	gui_hsl2rgb_hue_index(float h1)
{
	const float	a[6][2] = GUI_HSL2RGB_MATRIX1;
	int			i;

	i = 0;
	while (i < 6)
	{
		if ((a[i][0] <= h1) && (h1 <= a[i][1]))
			break ;
		i++;
	}
	return (i);
}

int	gui_hsl2rgb_values(float *rgb, float *cxo, float m, int i)
{
	const int	a[7][3] = GUI_HSL2RGB_MATRIX2;

	i %= 7;
	rgb[0] = cxo[a[i][0]] + m;
	rgb[1] = cxo[a[i][1]] + m;
	rgb[2] = cxo[a[i][2]] + m;
	return (0);
}

/*
** hue [0..360], saturation [0..100], luminosity [0..100]
** https://en.wikipedia.org/wiki/HSL_and_HSV
*/

int	gui_hsl2rgb(float h, float s, float l)
{
	float	cxo[3];
	float	rgb[3];
	int		i;

	h /= 60;
	s /= 100;
	l /= 100;
	cxo[0] = 1 - fabsf(2 * l - 1) * s;
	cxo[1] = cxo[0] * (1 - fabsf(fmodf(h, 2) - 1));
	cxo[2] = 0;
	i = gui_hsl2rgb_hue_index(h);
	(void)gui_hsl2rgb_values(&rgb[0], &cxo[0], l - (cxo[0] / 2), i);
	return (gui_hsl2rgb_int(&rgb[0]));
}

int	gui_init_colors(t_gui *g)
{
	int			i;
	int			j;
	int			rgb;
	float		lum;
	const float	hues[] = GUI_PLAYER_HUES1;

	i = 0;
	while (i < MAX_LUM_STEPS + 1)
		g->player_colors[0][i++] = BLOCK_DEFAULT_COLOR;
	i = 1;
	while (i < MAX_PLAYERS + 1)
	{
		j = 0;
		while (j < MAX_LUM_STEPS + 1)
		{
			lum = LUM_START;
			lum -= (float)j * (float)LUM_RANGE / (float)MAX_LUM_STEPS;
			rgb = gui_hsl2rgb(hues[i - 1], 100, lum);
			g->player_colors[i][j] = rgb;
			j++;
		}
		i++;
	}
	return (0);
}
