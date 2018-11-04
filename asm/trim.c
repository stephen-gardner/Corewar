/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:39:42 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/11 21:53:19 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*trim_left(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (i)
	{
		if (str[i] == 0)
		{
			str[0] = 0;
			return (str);
		}
		j = 0;
		while (str[i])
		{
			str[j] = str[i];
			j++;
			i++;
		}
		str[j] = 0;
	}
	return (str);
}

char	*trim_right(char *str)
{
	int	i;

	i = (int)ft_strlen(str) - 1;
	while ((i >= 0) && (ft_isspace(str[i])))
	{
		str[i] = 0;
		i--;
	}
	return (str);
}

char	*strip_comments(char *str)
{
	char	*ptr;

	ptr = ft_strchr(str, COMMENT_CHAR);
	if (ptr != NULL)
		ptr[0] = 0;
	ptr = ft_strchr(str, ';');
	if (ptr != NULL)
		ptr[0] = 0;
	return (str);
}
