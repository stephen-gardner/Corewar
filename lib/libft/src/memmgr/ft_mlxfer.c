/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlxfer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 14:58:34 by sgardner          #+#    #+#             */
/*   Updated: 2017/12/04 22:17:12 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memmgr.h"

t_mlink	*ft_mlxfer(t_mlink *mlink, t_mchain *mchain)
{
	void	*ptr;
	size_t	size;
	t_mlink	*next;

	ptr = mlink->ptr;
	size = mlink->size;
	next = ft_mlremove(mlink);
	ft_mladd(mchain, ptr, size);
	return (next);
}
