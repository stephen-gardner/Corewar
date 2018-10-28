/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 22:03:27 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/27 22:12:49 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_sti(t_core *core, t_proc *p)
{
	t_instr	*instr;
	t_uint	off;

	instr = &p->instr;
	off = read_data(core, instr, 1) + read_data(core, instr, 2);
	write_data(core, ABS_POS(core->arena, p->pc, off), p, 0);
	return (p->carry);
}
