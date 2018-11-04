/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:22:42 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/02 02:57:31 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	error_invalid_operand(char *line, char *s1, char *s2, t_asm *a)
{
	ft_printf(C_YELLOW"LINE:"C_END" %s\n", line);
	ft_printf(C_RED"ERROR:"C_END" invalid operand type:");
	ft_printf("%s for instruction %s\n", s1, s2);
	clean_up(a);
	exit(0);
}

void	error_bad_operand_count(char *line, t_asm *a)
{
	ft_printf(C_YELLOW"LINE:"C_END" %s\n", line);
	ft_printf(C_RED"ERROR:"C_END" wrong number of operands\n");
	clean_up(a);
	exit(0);
}
