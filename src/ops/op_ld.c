/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 07:37:26 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/05 07:25:51 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_ld(t_core *core, t_proc *p, t_instr *instr)
{
	int32_t	*dst;

	dst = (int32_t *)instr->args[1];
	*dst = read_arg(core, p, 0);
	return (!*dst);
}
