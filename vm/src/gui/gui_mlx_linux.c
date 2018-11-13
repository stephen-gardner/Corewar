/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_mlx_linux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 02:37:42 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/09 03:24:55 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"
#define NORMI2 t_xvar *xv, t_win_list *w, t_img *i, int x, int y, int c, char *

int	mlx_string_put_to_image(NORMI2 s)
{
	XGCValues	xgcv;

	xgcv.foreground = mlx_int_get_good_color(xv, c);
	XChangeGC(xv->display, w->gc, GCForeground, &xgcv);
	XDrawImageString(xv->display, i->pix, w->gc, x, y, s, strlen(s));
	if (xv->do_flush)
		XFlush(xv->display);
	return (0);
}
