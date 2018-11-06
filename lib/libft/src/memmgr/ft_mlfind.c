/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlfind.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 01:54:10 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/06 00:30:07 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memmgr.h"

static t_mlink	*find_mlink(t_mchain *mchain, void *ptr)
{
	t_mlink	*mlink;

	mlink = mchain->start;
	while (mlink && mlink->ptr != ptr)
		mlink = mlink->next;
	return (mlink);
}

t_mlink			*ft_mlfind(t_mchain *mchain, void *ptr)
{
	t_mchain	*mchead;
	t_mlink		*mlink;

	if (mchain)
		return (find_mlink(mchain, ptr));
	mchead = *ft_mcgetall();
	while (mchead)
	{
		if ((mlink = find_mlink(mchead, ptr)))
			return (mlink);
		mchead = mchead->next;
	}
	return (NULL);
}
