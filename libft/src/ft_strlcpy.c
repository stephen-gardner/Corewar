/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 16:02:40 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 17:29:47 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *s1, const char *s2, size_t n)
{
	size_t	len;

	len = 0;
	if (n)
	{
		--n;
		while (len < n && s2[len])
		{
			s1[len] = s2[len];
			++len;
		}
		s1[len] = '\0';
	}
	if (s2[len])
		len += ft_strlen(s2 + len);
	return (len);
}
