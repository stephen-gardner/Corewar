/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 07:37:26 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/03 23:14:17 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_ld(t_core *core, t_proc *p, t_instr *instr)
{
	t_uint	*dst;

	dst = (t_uint *)instr->args[1];
	*dst = read_arg(core, p, 0);
	return (!*dst);
}
