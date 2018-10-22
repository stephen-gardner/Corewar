/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlappend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 20:37:31 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/06 00:29:26 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memmgr.h"

t_mlink	*ft_mlappend(t_mchain *mchain, void *ptr, size_t size)
{
	t_mlink	*mlink;

	if (!(mlink = ft_mladd(mchain, ptr, size)))
		return (NULL);
	if (mchain->end == mlink)
		return (mlink);
	mchain->start = mlink->next;
	mchain->end->next = mlink;
	mchain->end = mlink;
	mlink->next = NULL;
	return (mlink);
}
