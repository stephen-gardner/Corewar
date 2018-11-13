/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 23:21:55 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/12 21:18:38 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	whitespace_transform(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (IS_SPACE(str[i]))
			str[i] = ' ';
		i++;
	}
	return ;
}

void	string_shift_left(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	return ;
}

void	whitespace_consolidate(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((IS_SPACE(str[i])) && (IS_SPACE(str[i + 1])))
		{
			string_shift_left(&str[i]);
			i = 0;
			continue ;
		}
		i++;
	}
	return ;
}

void	whitespace_trim(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((IS_SPACE(str[i])) && (str[i + 1] == SEPARATOR_CHAR))
		{
			string_shift_left(&str[i]);
			i = 0;
			continue ;
		}
		if ((IS_SPACE(str[i + 1])) && (str[i] == SEPARATOR_CHAR))
		{
			i++;
			string_shift_left(&str[i]);
			i = 0;
			continue ;
		}
		i++;
	}
	return ;
}

void	process_whitespace(char *str)
{
	whitespace_transform(str);
	whitespace_consolidate(str);
	whitespace_trim(str);
	return ;
}
