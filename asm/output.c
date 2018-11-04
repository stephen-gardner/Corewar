/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:52:17 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/01 23:34:25 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		update_acb(int acb, int index, int op_type)
{
	int	tmp;
	int shift;

	tmp = 0;
	shift = 0;
	if (op_type == T_REG)
		tmp = REG_CODE;
	if (op_type == T_DIR)
		tmp = DIR_CODE;
	if (op_type == T_IND)
		tmp = IND_CODE;
	if (index == 0)
		shift = 6;
	if (index == 1)
		shift = 4;
	if (index == 2)
		shift = 2;
	tmp = (tmp << shift);
	return (acb + tmp);
}

void	output_write_data(t_asm *a, t_instruction *ptr, int *i, int j)
{
	if (ptr->op_types[j] == T_REG)
		a->body[(*i)++] = (char)ptr->op_values[j];
	if ((ptr->op_types[j] == T_IND) ||
			((ptr->op_types[j] == T_DIR) && (ptr->short_direct == 1)))
	{
		a->body[(*i)++] = (char)(ptr->op_values[j] >> 8);
		a->body[(*i)++] = (char)ptr->op_values[j];
	}
	if ((ptr->op_types[j] == T_DIR) && (ptr->short_direct == 0))
	{
		a->body[(*i)++] = (char)(ptr->op_values[j] >> 24);
		a->body[(*i)++] = (char)(ptr->op_values[j] >> 16);
		a->body[(*i)++] = (char)(ptr->op_values[j] >> 8);
		a->body[(*i)++] = (char)ptr->op_values[j];
	}
	return ;
}

void	generate_output(t_asm *a)
{
	int				i;
	int				j;
	t_instruction	*ptr;

	a->header.magic = betole(COREWAR_EXEC_MAGIC);
	a->header.prog_size = betole(a->prog_size);
	ptr = a->instruction;
	i = 0;
	while (ptr)
	{
		if (ptr->type == T_REG)
		{
			a->body[i++] = (char)ptr->opcode;
			if (ptr->has_acb)
				a->body[i++] = (char)ptr->acb;
			j = 0;
			while (j < ptr->arg_count)
			{
				output_write_data(a, ptr, &i, j);
				j++;
			}
		}
		ptr = ptr->next;
	}
	return ;
}
