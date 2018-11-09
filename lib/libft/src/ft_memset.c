/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 01:15:29 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/12 21:06:52 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	t_byte	*dst;
	t_byte	b;
	size_t	i;

	dst = (t_byte *)s;
	b = (t_byte)c;
	i = 0;
	while (i < n)
		dst[i++] = b;
	return (s);
}
