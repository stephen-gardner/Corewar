/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_nop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 04:46:57 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/03 18:31:41 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_nop(t_core *core, t_proc *p, t_instr *instr)
{
	UNUSED(core);
	UNUSED(p);
	UNUSED(instr);
	return (p->carry);
}
