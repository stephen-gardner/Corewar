/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 03:27:55 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/10 14:21:14 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

int	complex_instruction(char *data, t_op op)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (i < op.arg_count)
	{
		if (get_arg_type(data[1], i) == REG_CODE)
			j += print_register(data, j);
		else if (get_arg_type(data[1], i) == IND_CODE)
			j += print_ind(data, j);
		else if (get_arg_type(data[1], i) == DIR_CODE)
		{
			if (op.short_direct == 1)
				j += print_short_direct(data, j);
			else
				j += print_int_direct(data, j);
		}
		if (++i < op.arg_count)
			ft_printf(", ");
		else
			ft_printf("\n");
	}
	return (j);
}

int	print_instruction(char *data, t_op op)
{
	ft_printf("\t%s\t", op.name);
	if (op.needs_acb)
		return (complex_instruction(data, op));
	if (op.short_direct)
	{
		ft_printf("%c%d\n", DIRECT_CHAR, chartoshort(&data[1]));
		return (3);
	}
	else
	{
		ft_printf("%c%d\n", DIRECT_CHAR, chartoint(&data[1]));
		return (5);
	}
}
