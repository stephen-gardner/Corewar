/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 11:54:05 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 16:39:03 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (IS_ALNUM(str[i]))
		{
			str[i] = (char)TO_UPPER(str[i]);
			++i;
			while (IS_ALNUM(str[i]))
			{
				str[i] = (char)TO_LOWER(str[i]);
				++i;
			}
		}
		else
			++i;
	}
	return (str);
}
