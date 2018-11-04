/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 21:23:17 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/03 17:42:02 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_ldi(t_core *core, t_proc *p, t_instr *instr)
{
	t_uint	*dst;
	t_uint	off;

	dst = (t_uint *)instr->args[2];
	off = read_arg(core, p, 0) + read_arg(core, p, 1);
	*dst = read_core(core, IDX_POS(core->arena, p->pc, off), REG_SIZE, FALSE);
	return (p->carry);
}
