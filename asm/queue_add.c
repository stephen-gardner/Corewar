/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:53:20 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/02 02:23:03 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_label_to_queue(t_asm *a, char *label)
{
	t_instruction	*ptr;
	t_instruction	*tail;

	ptr = ft_memalloc(sizeof(t_instruction));
	ptr->type = T_LAB;
	ptr->label = ft_strdup(label);
	ptr->label[ft_strlen(ptr->label) - 1] = 0;
	ptr->original = a->split[a->lines - 1];
	ptr->address = a->prog_size;
	if (a->instruction == NULL)
		a->instruction = ptr;
	else
	{
		tail = a->instruction;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = ptr;
	}
	return ;
}

t_in	*queue_prepare(t_asm *a, char *name, char *oper)
{
	t_op			instr;
	t_instruction	*ptr;

	instr = find_instruction(name);
	ptr = ft_memalloc(sizeof(t_instruction));
	ptr->type = T_REG;
	ptr->original = a->split[a->lines - 1];
	ptr->opcode = instr.opcode;
	ptr->has_acb = instr.needs_acb;
	ptr->address = a->prog_size;
	ptr->i_name = ft_strdup(name);
	ptr->i_oper = ft_strdup(oper);
	ptr->operands = ft_strsplit(oper, SEPARATOR_CHAR);
	if (count_char_array(ptr->operands) != instr.arg_count)
		error_bad_operand_count(ptr->original, a);
	ptr->arg_count = instr.arg_count;
	ptr->short_direct = instr.short_direct;
	ptr->size = 1 + instr.needs_acb;
	return (ptr);
}

void	add_to_queue(t_asm *a, t_in *ptr)
{
	t_instruction	*tail;

	if (a->instruction == NULL)
		a->instruction = ptr;
	else
	{
		tail = a->instruction;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = ptr;
	}
	return ;
}

void	add_operand_size(int type, t_in *ptr, t_op instr)
{
	if (type == T_REG)
		ptr->size += 1;
	else if ((type == T_IND) ||
			((type == T_DIR) && (instr.short_direct == 1)))
		ptr->size += 2;
	else if ((type == T_DIR) && (instr.short_direct == 0))
		ptr->size += 4;
	return ;
}

void	add_instruction_to_queue(t_asm *a, char *name, char *oper)
{
	t_op			instr;
	t_instruction	*ptr;
	int				i;
	int				type;

	instr = find_instruction(name);
	ptr = queue_prepare(a, name, oper);
	i = 0;
	while (i < instr.arg_count)
	{
		type = get_operand_type(ptr->operands[i]);
		if ((instr.arg[i] & type) == 0)
			error_invalid_operand(ptr->original, ptr->operands[i], name, a);
		ptr->op_types[i] = type;
		add_operand_size(type, ptr, instr);
		ptr->acb = update_acb(ptr->acb, i, type);
		ptr->op_values[i] = ft_atoi(ptr->operands[i]);
		i++;
	}
	a->prog_size += ptr->size;
	return (add_to_queue(a, ptr));
}
