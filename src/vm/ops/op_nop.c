/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_nop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 04:46:57 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/31 04:47:35 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool	op_nop(t_core *core, t_proc *p)
{
	UNUSED(core);
	UNUSED(p);
	return (p->carry);
}
