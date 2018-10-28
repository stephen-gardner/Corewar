/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 21:23:17 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/27 21:56:26 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_ldi(t_core *core, t_proc *p)
{
	t_instr	*instr;
	t_uint	*dst;
	t_uint	off;

	instr = &p->instr;
	dst = (t_uint *)instr->args[2];
	off = read_data(core, instr, 0) + read_data(core, instr, 1);
	*dst = read_core(core, IDX_POS(core->arena, p->pc, off), REG_SIZE);
	return (p->carry);
}
