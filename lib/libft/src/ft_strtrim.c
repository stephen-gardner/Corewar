/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 23:39:13 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 17:09:59 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	trim_dir(const char *s, size_t index, t_bool forward)
{
	while (s[index] == ' ' || s[index] == '\t' || s[index] == '\n')
		index = (forward) ? index + 1 : index - 1;
	return (index);
}

char			*ft_strtrim(const char *s)
{
	size_t	len;

	s += trim_dir(s, 0, TRUE);
	if ((len = ft_strlen(s)))
		len = trim_dir(s, len - 1, FALSE) + 1;
	return (ft_strsub(s, 0, len));
}
