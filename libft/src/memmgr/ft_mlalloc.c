/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 00:42:57 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/04 21:49:40 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memmgr.h"

void	*ft_mlalloc(t_mchain *mchain, size_t size)
{
	void	*ptr;

	if (!(ptr = ft_memalloc(size)))
		return (NULL);
	if (!ft_mladd(mchain, ptr, size))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
