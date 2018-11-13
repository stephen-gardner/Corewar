/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 03:25:40 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/01 23:40:20 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		betole(int x)
{
	int	result;

	result = (x >> 24) & 0xFF;
	result += (x >> 8) & 0xFF00;
	result += (x << 8) & 0xFF0000;
	result += x << 24;
	return (result);
}

int		chartoint(char *array)
{
	int	result;

	result = (unsigned char)array[3];
	result += (unsigned char)array[2] * 256;
	result += (unsigned char)array[1] * 256 * 256;
	result += (unsigned char)array[0] * 256 * 256 * 256;
	return (result);
}

short	chartoshort(char *array)
{
	short	result;

	result = (unsigned char)array[1];
	result += (unsigned char)array[0] * 256;
	return (result);
}

bool	is_valid_magic(t_header *header)
{
	int	magic;

	magic = betole(header->magic);
	if (magic == COREWAR_EXEC_MAGIC)
		return (true);
	return (false);
}

int		get_arg_type(char arg_byte, int arg_number)
{
	if (arg_number == 0)
		return ((arg_byte >> 6) & 3);
	if (arg_number == 1)
		return ((arg_byte >> 4) & 3);
	if (arg_number == 2)
		return ((arg_byte >> 2) & 3);
	return (arg_byte & 3);
}
