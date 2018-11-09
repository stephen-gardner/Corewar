/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_gui_hooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:04:16 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/07 18:08:03 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_gui.h"

int	corewar_gui_key_hook(int keycode, t_corewar_gui *g)
{
	if ((keycode == KEY_ESCAPE) || (keycode == KEY_Q))
	{
		(void)corewar_gui_clean_up(g);
		exit(0);
	}
	else if (corewar_gui_is_numeric_key(keycode))
		(void)corewar_gui_set_cpf_to_numeric_key(keycode, g);
	else if (keycode == KEY_SPACE)
		g->state ^= 1;
	else if ((keycode != KEY_PLUS) && (keycode != KEY_MINUS))
		ft_printf("you pressed: %d, %s\n", keycode, GUI_CONTROLS_INFO);
	return (0);
}

int	corewar_gui_mouse_hook(int button, int x, int y, t_corewar_gui *g)
{
	(void)button;
	(void)x;
	(void)y;
	(void)g;
	return (0);
}

int	corewar_gui_expose_hook(t_corewar_gui *g)
{
	(void)g;
	return (0);
}
