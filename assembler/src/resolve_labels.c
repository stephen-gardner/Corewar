/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_labels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:58:19 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/02 02:57:48 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	label_not_found(char *line, char *label, t_asm *a)
{
	ft_printf(C_YELLOW"LINE:"C_END" %s\n", line);
	ft_printf(C_RED"ERROR:"C_END" label not found '%s'\n", label);
	clean_up(a);
	exit(0);
}

void		fix_operand_values(t_asm *a, int i, t_instruction *ptr)
{
	t_instruction	*label;

	if ((is_direct_label(ptr->operands[i])) ||
			(is_indirect_label(ptr->operands[i])))
	{
		label = find_label(a, ptr->operands[i]);
		if (label == NULL)
			label_not_found(ptr->original, ptr->operands[i], a);
		else
			ptr->op_values[i] = label->address - ptr->address;
	}
	else if (is_register(ptr->operands[i]))
		ptr->op_values[i] = ft_atoi(&ptr->operands[i][1]);
	else if (is_indirect(ptr->operands[i]))
		ptr->op_values[i] = ft_atoi(ptr->operands[i]);
	else if (is_direct(ptr->operands[i]))
		ptr->op_values[i] = ft_atoi(&ptr->operands[i][1]);
	return ;
}

void		resolve_labels(t_asm *a)
{
	t_instruction	*ptr;
	int				i;

	ptr = a->instruction;
	while (ptr != NULL)
	{
		if (ptr->type == T_REG)
		{
			i = 0;
			while (i < ptr->arg_count)
			{
				fix_operand_values(a, i, ptr);
				i++;
			}
		}
		ptr = ptr->next;
	}
	return ;
}
