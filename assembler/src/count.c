/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 21:07:02 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/12 21:06:30 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

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
	split = ft_strsplit(str, SEPARATOR_CHAR);
	count = count_char_array(split);
	free(split);
	return (count);
}
