/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coreio.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 01:09:10 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/31 04:31:10 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_uint	read_core(t_core *core, t_byte *src, int n, t_bool trunc)
{
	t_byte	*dst;
	t_uint	res;
	int		i;

	i = -1;
	res = 0;
	dst = (t_byte *)&res;
	while (++i < n)
		dst[(n - 1) - i] = *ABS_POS(core->arena, src, i);
	if (n == IND_SIZE || trunc)
		res >>= ((DIR_SIZE - IND_SIZE) << 3);
	return (res);
}

t_uint	read_data(t_core *core, t_instr *instr, int a)
{
	if (instr->atypes[a] & T_R)
		return (*((t_uint *)instr->args[a]));
	if (instr->atypes[a] & T_I)
		return (read_core(core, instr->args[a], IND_SIZE, FALSE));
	return (read_core(core, instr->args[a], DIR_SIZE, instr->op->trunc));
}

void	write_data(t_core *core, t_byte *dst, t_proc *p, int a)
{
	t_byte	*src;
	t_byte	*tmp;
	int		n;
	int		i;

	i = -1;
	src = p->instr.args[a];
	n = (p->instr.atypes[a] == T_I) ? IND_SIZE : DIR_SIZE;
	while (++i < n)
	{
		tmp = ABS_POS(core->arena, dst, ((n - 1) - i));
		*tmp = src[i];
		core->owner[tmp - core->arena] = p->champ - core->champions;
	}
}
