/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 02:05:05 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 17:30:56 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*dst;
	size_t	i;

	dst = s1 + ft_strlen(s1);
	i = 0;
	while (i < n && s2[i])
	{
		dst[i] = s2[i];
		++i;
	}
	dst[i] = '\0';
	return (s1);
}
