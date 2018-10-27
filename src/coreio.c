/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coreio.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 01:09:10 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/27 07:31:45 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_uint	read_data(t_core *core, t_instr *instr, int a)
{
	t_uint	res;
	t_byte	*dst;
	int		bytes;
	int		i;

	if (instr->atypes[a] == T_R)
		return (*((t_uint *)instr->args[a]));
	res = 0;
	dst = (t_byte *)&res;
	bytes = (instr->atypes[a] == T_I) ? IND_SIZE : DIR_SIZE;
	i = 0;
	while (i < bytes)
	{
		dst[i] = *ABS_POS(core->arena, instr->args[a], i);
		++i;
	}
	res >>= ((DIR_SIZE - bytes) << 3);
	return (res);
}

void	write_data(t_core *core, t_byte *dst, t_proc *p, int a)
{
	t_byte	*src;
	t_byte	*tmp;
	int		bytes;
	int		i;

	i = 0;
	src = (t_byte *)&p->instr.args[a];
	bytes = (p->instr.atypes[a] == T_I) ? IND_SIZE : DIR_SIZE;
	while (i < bytes)
	{
		tmp = ABS_POS(core->arena, dst, i);
		*tmp = src[i];
		core->owner[tmp - core->arena] = p->champ - core->champions;
		++i;
	}
}
