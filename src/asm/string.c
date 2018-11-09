/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:50:27 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/01 23:37:33 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool	string_is_integer(char *str)
{
	int		i;
	bool	result;

	i = 0;
	result = false;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			result = false;
			break ;
		}
		result = true;
		i++;
	}
	return (result);
}

bool	string_is_label(char *str)
{
	int	i;

	if ((str == NULL) || (str[0] == 0))
		return (false);
	i = 0;
	while (str[i])
	{
		if (ft_strchr(LABEL_CHARS, str[i]) == NULL)
			return (false);
		i++;
	}
	return (true);
}
