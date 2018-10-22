/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 19:11:14 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 17:26:20 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;

	if ((res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		ft_stpcpy(ft_stpcpy(res, s1), s2);
	return (res);
}
