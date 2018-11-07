/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 08:19:47 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/05 04:22:48 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_or(t_core *core, t_proc *p, t_instr *instr)
{
	uint32_t	*dst;

	dst = (uint32_t *)instr->args[2];
	*dst = (uint32_t)read_arg(core, p, 0) | (uint32_t)read_arg(core, p, 1);
	return (!*dst);
}
