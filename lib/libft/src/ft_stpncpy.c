/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stpncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 01:16:45 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 16:41:39 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stpncpy(char *s1, const char *s2, size_t n)
{
	char	*res;
	size_t	i;

	i = 0;
	while (i < n && s2[i])
	{
		s1[i] = s2[i];
		++i;
	}
	res = s1 + i;
	while (i < n)
		s1[i++] = '\0';
	return (res);
}
