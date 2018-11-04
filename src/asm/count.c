/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 21:07:02 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/04 14:43:51 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			count_matching_chars(char *str, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int			count_operands(char *str)
{
	int		count;
	char	**split;

	if (str == NULL)
		return (0);
	split = ft_strsplit2(str, SEPARATOR_CHAR);
	count = count_char_array(split);
	destroy_char_array(split, count);
	return (count);
}
