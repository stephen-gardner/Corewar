/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 01:30:13 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/02 00:05:25 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	hexdump_write_operands(t_instruction *ptr, char *res, int *i, int j)
{
	if (ptr->op_types[j] == T_REG)
		res[(*i)++] = (char)ptr->op_values[j];
	if ((ptr->op_types[j] == T_IND) ||
			((ptr->op_types[j] == T_DIR) && (ptr->short_direct == 1)))
	{
		res[(*i)++] = (char)(ptr->op_values[j] >> 8);
		res[(*i)++] = (char)ptr->op_values[j];
	}
	if ((ptr->op_types[j] == T_DIR) && (ptr->short_direct == 0))
	{
		res[(*i)++] = (char)(ptr->op_values[j] >> 24);
		res[(*i)++] = (char)(ptr->op_values[j] >> 16);
		res[(*i)++] = (char)(ptr->op_values[j] >> 8);
		res[(*i)++] = (char)ptr->op_values[j];
	}
}

char	*hexdump_bytes(t_instruction *ptr, int *count)
{
	char	*res;
	int		i;
	int		j;

	res = ft_memalloc(MAX_INSTR_BYTES + 1);
	i = 0;
	res[i++] = (char)ptr->opcode;
	if (ptr->has_acb)
		res[i++] = (char)ptr->acb;
	j = 0;
	while (j < ptr->arg_count)
		hexdump_write_operands(ptr, res, &i, j++);
	*count = i;
	return (res);
}

void	hexdump_print(t_instruction *ptr, char *bytes, int count)
{
	int	i;
	int	tab;

	i = ft_strlen(ptr->i_name) + ft_strlen(ptr->i_oper) + 1;
	tab = i / TAB_SIZE;
	i = COMMENT_TABS - tab;
	while (i--)
		ft_printf("\t");
	ft_printf("%c ", COMMENT_TAB_CHAR);
	i = 0;
	while (i < count)
	{
		ft_printf("%02x", (unsigned char)bytes[i]);
		if (i < count - 1)
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
	return ;
}

void	generate_hexdump(t_asm *a)
{
	int				j;
	t_instruction	*ptr;
	char			*bytes;

	ft_printf("%s \"%s\"\n", NAME_CMD_STRING, a->header.prog_name);
	ft_printf("%s \"%s\"\n", COMMENT_CMD_STRING, a->header.comment);
	ptr = a->instruction;
	while (ptr)
	{
		if (ptr->type == T_LAB)
			ft_printf("%s%c\n", ptr->label, LABEL_CHAR);
		if (ptr->type == T_REG)
		{
			ft_printf("\t%s %s", ptr->i_name, ptr->i_oper);
			bytes = hexdump_bytes(ptr, &j);
			hexdump_print(ptr, bytes, j);
			free(bytes);
		}
		ptr = ptr->next;
	}
}
