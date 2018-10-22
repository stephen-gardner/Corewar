/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 01:15:21 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/06 19:11:49 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	const t_byte	*src;
	t_byte			*dst;

	if (s1 == s2)
		return (s1);
	if (s1 < s2)
		return (ft_memcpy(s1, s2, n));
	src = (const t_byte *)s2;
	dst = (t_byte *)s1;
	while (n--)
		dst[n] = src[n];
	return (s1);
}
