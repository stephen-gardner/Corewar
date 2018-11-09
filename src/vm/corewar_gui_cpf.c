/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_gui_cpf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:05:46 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/07 20:55:25 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_gui.h"

int	corewar_gui_calc_fps(t_corewar_gui *g)
{
	time_t		tloc;
	static	int	current;
	static	int	previous;
	static	int	counter;

	counter++;
	current = time(&tloc);
	if (current == previous + 1)
	{
		g->fps = counter;
		counter = 0;
		previous = current;
	}
	else if (previous != current)
		previous = current;
	return (0);
}

int	corewar_gui_set_cpf_to_numeric_key(int keycode, t_corewar_gui *g)
{
	const int	keys[] = GUI_NUMERIC_KEY_ARRAY;
	const int	values[] = GUI_NUMERIC_KEY_VALUES;
	int			i;

	i = 0;
	while (i < (int)(sizeof(keys) / sizeof(int)))
	{
		if (keycode == keys[i])
		{
			g->cpf = values[i];
			return (1);
		}
		i++;
	}
	return (0);
}

int	corewar_gui_increment_cpf(int keycode, t_corewar_gui *g)
{
	if ((keycode == KEY_PLUS) && (g->cpf < CPF_MAX))
		g->cpf += 1;
	else if ((keycode == KEY_MINUS) && (g->cpf > 0))
		g->cpf -= 1;
	return (0);
}

int	corewar_gui_key_repeat(int keycode, t_corewar_gui *g)
{
	if ((keycode == KEY_PLUS) || (keycode == KEY_MINUS))
		(void)corewar_gui_increment_cpf(keycode, g);
	return (0);
}

int	corewar_gui_is_numeric_key(int keycode)
{
	if ((keycode == KEY_1) || (keycode == KEY_2) || (keycode == KEY_3))
		return (1);
	else if ((keycode == KEY_4) || (keycode == KEY_5) || (keycode == KEY_6))
		return (1);
	else if ((keycode == KEY_7) || (keycode == KEY_8) || (keycode == KEY_9))
		return (1);
	else if (keycode == KEY_0)
		return (1);
	return (0);
}
