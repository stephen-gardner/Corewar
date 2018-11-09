/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_mlx_macos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 02:39:34 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/09 03:25:09 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#define NORM1 void *mlx, void *win, void *img, int x, int y, int c, char *

int	mlx_string_put_to_image(NORM1 s)
{
	(void)img;
	return (mlx_string_put(mlx, win, x, y, c, s));
}
