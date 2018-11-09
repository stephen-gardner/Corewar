/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 00:24:51 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/07 03:45:09 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <unistd.h>

t_bool	op_aff(t_core *core, t_proc *p, t_instr *instr)
{
	char	c;

	UNUSED(instr);
	if (core->quiet)
		return (p->carry);
	c = read_arg(core, p, 0) % 256;
	write(STDOUT_FILENO, &c, 1);
	return (p->carry);
}
