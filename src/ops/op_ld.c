/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 07:37:26 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/27 23:50:39 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_ld(t_core *core, t_proc *p)
{
	t_instr	*instr;
	t_uint	*dst;
	t_byte	*src;

	instr = &p->instr;
	src = IDX_POS(core->arena, p->pc, read_data(core, instr, 0));
	dst = (t_uint *)instr->args[1];
	*dst = read_core(core, src, REG_SIZE);
	return (!*dst);
}
