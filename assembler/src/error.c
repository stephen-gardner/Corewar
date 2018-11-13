/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 21:06:12 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/12 21:12:19 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	header_error(char *msg, t_asm *a)
{
	ft_printf(C_RED "ERROR:" C_END " %s\n", msg);
	free(a->split);
	if (a->tmp != NULL)
		free(a->tmp);
	close(a->fd);
	free(a);
	exit(0);
	return ;
}

void	print_error(void)
{
	ft_printf(C_RED "ERROR:" C_END " %s\n", strerror(errno));
	return ;
}

void	clean_up(t_asm *a)
{
	t_instruction	*ptr;
	t_instruction	*next;

	ptr = a->instruction;
	while (ptr != NULL)
	{
		next = ptr->next;
		if (ptr->type == T_LAB)
			free(ptr->label);
		else if (ptr->type == T_REG)
		{
			free(ptr->i_name);
			free(ptr->i_oper);
			free(ptr->operands);
		}
		free(ptr);
		ptr = next;
	}
	free(a->split);
	if (a->tmp != NULL)
		free(a->tmp);
	close(a->fd);
	free(a);
	return ;
}
