/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 20:24:30 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/28 00:18:05 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_zjmp(t_core *core, t_proc *p)
{
	t_uint	val;

	if (p->carry)
	{
		val = read_data(core, &p->instr, 0);
		p->instr.epc = IDX_POS(core->arena, p->pc, val);
	}
	else
		p->instr.epc += DIR_SIZE;
	return (p->carry);
}
