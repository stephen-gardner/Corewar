/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlarray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:15:13 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 18:03:56 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memmgr.h"

void	**ft_mlarray(t_mchain *mchain)
{
	void		**array;
	t_mlink		*current;
	size_t		size;
	int			i;

	size = sizeof(void *) * (mchain->link_count + 1);
	if (!(array = ft_memalloc(size)))
		return (NULL);
	current = mchain->start;
	i = 0;
	while (i < mchain->link_count)
	{
		array[i++] = current->ptr;
		current = current->next;
	}
	return (array);
}
