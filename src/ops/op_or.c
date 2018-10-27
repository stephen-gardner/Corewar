/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 08:19:47 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/27 08:46:02 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_or(t_core *core, t_proc *p)
{
	t_instr	*instr;
	t_uint	*dst;

	instr = &p->instr;
	dst = (t_uint *)instr->args[2];
	*dst = read_data(core, instr, 0) | read_data(core, instr, 1);
	return (!*dst);
}
