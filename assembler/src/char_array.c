/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:59:31 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/11 21:52:44 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	destroy_char_array(char **array, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (array[i] != NULL)
			free(array[i]);
		i++;
	}
	free(array);
	return ;
}

void	insert_into_char_array(t_asm *a, char *str)
{
	char	**new_array;
	int		i;

	new_array = ft_memalloc((a->lines + 1) * sizeof(char *));
	i = 0;
	while (i < a->lines)
	{
		new_array[i] = a->split[i];
		i++;
	}
	new_array[i] = str;
	if (a->split != NULL)
		free(a->split);
	a->split = new_array;
	a->lines += 1;
	return ;
}

int		count_char_array(char **array)
{
	int i;

	if (array == NULL)
		return (0);
	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}
