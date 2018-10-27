/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 07:45:38 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/27 08:03:14 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_st(t_core *core, t_proc *p)
{
	t_instr	*instr;
	t_uint	val;
	t_uint	off;

	instr = &p->instr;
	val = read_data(core, instr, 0);
	off = read_data(core, instr, 1);
	instr->args[0] = (t_byte *)&val;
	instr->atypes[0] = T_R;
	write_data(core, IDX_POS(core->arena, p->pc, off), p, 0);
	return (p->carry);
}
