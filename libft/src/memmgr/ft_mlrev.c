/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlrev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:42:33 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/06 00:31:04 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memmgr.h"

t_mlink	*ft_mlrev(t_mchain *mchain)
{
	t_mlink		*current;
	t_mlink		*prev;
	t_mlink		*next;

	if (!(current = mchain->start))
		return (NULL);
	if (mchain->end == current)
		return (current);
	mchain->end = current;
	prev = NULL;
	while (TRUE)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		if (!next)
			break ;
		current = next;
	}
	return ((mchain->start = current));
}
