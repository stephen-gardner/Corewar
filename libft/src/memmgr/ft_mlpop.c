/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlpop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:25:01 by sgardner          #+#    #+#             */
/*   Updated: 2018/07/10 02:07:46 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memmgr.h"

t_mlink	*ft_mlpop(t_mchain *mchain)
{
	t_mlink		*next;

	if (!mchain->start)
		return (NULL);
	if (mchain->end == mchain->start)
		mchain->end = NULL;
	next = mchain->start->next;
	if (CANFREE(mchain->start))
		free(mchain->start->ptr);
	free(mchain->start);
	mchain->link_count--;
	return ((mchain->start = next));
}
