/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 19:45:55 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 17:07:57 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;

	if (!*s2)
		return ((char *)s1);
	while (*s1)
	{
		i = 0;
		while (s1[i])
		{
			if (s1[i] != s2[i])
				break ;
			++i;
		}
		if (!s2[i])
			return ((char *)s1);
		++s1;
	}
	return (NULL);
}
