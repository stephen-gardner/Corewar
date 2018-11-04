/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:47:01 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/02 00:33:40 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool	is_direct(char *str)
{
	if (str[0] != '%')
		return (false);
	if (string_is_integer(&str[1]))
		return (true);
	if ((str[1] == LABEL_CHAR) && (string_is_label(&str[2])))
		return (true);
	return (false);
}

bool	is_indirect(char *str)
{
	if (string_is_integer(str))
		return (true);
	if ((str[0] == LABEL_CHAR) && (string_is_label(&str[1])))
		return (true);
	return (false);
}

bool	is_register(char *str)
{
	int i;

	if (str[0] != 'r')
		return (false);
	i = ft_atoi(&str[1]);
	if ((i >= 1) && (i <= REG_NUMBER))
		return (true);
	return (false);
}

int		get_operand_type(char *op)
{
	if (is_direct(op))
		return (T_DIR);
	if (is_indirect(op))
		return (T_IND);
	if (is_register(op))
		return (T_REG);
	return (0);
}

bool	is_valid_operand(char *str)
{
	char	**split;
	char	*s;
	int		i;

	split = ft_strsplit(str, SEPARATOR_CHAR);
	i = 0;
	while (split[i] != NULL)
	{
		s = split[i];
		if ((is_direct(s)) || (is_indirect(s)) || (is_register(s)))
			i++;
		else
		{
			free_split(split);
			return (false);
		}
	}
	free_split(split);
	return (true);
}
