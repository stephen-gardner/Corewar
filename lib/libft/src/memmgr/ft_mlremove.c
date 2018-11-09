/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlremove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 01:28:57 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 18:04:58 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memmgr.h"

t_mlink	*ft_mlremove(t_mlink *mlink)
{
	t_mchain	*mchain;
	t_mlink		**current;
	t_mlink		*prev;

	mchain = mlink->mchain;
	prev = NULL;
	current = &mchain->start;
	while (*current != mlink)
	{
		prev = *current;
		current = &(*current)->next;
	}
	*current = (*current)->next;
	if (!*current)
		mchain->end = prev;
	free(mlink);
	--mchain->link_count;
	return (*current);
}
