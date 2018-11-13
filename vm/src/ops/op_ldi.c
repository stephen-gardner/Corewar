/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 21:23:17 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/04 16:25:38 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_ldi(t_core *core, t_proc *p, t_instr *instr)
{
	int32_t	*dst;
	int32_t	off;

	dst = (int32_t *)instr->args[2];
	off = read_arg(core, p, 0) + read_arg(core, p, 1);
	*dst = read_core(core, IDX_POS(core->arena, p->pc, off), REG_SIZE, FALSE);
	return (p->carry);
}
