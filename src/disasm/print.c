/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 03:26:25 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/03 03:51:33 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

int	print_prog_info(t_header *header)
{
	ft_printf("%s\t\t\"%s\"\n", NAME_CMD_STRING, header->prog_name);
	ft_printf("%s\t\"%s\"\n", COMMENT_CMD_STRING, header->comment);
	return (0);
}

int	print_register(char *data, int index)
{
	ft_printf("r%d", (char)data[index]);
	return (1);
}

int	print_ind(char *data, int index)
{
	ft_printf("%d", chartoshort(&data[index]));
	return (2);
}

int	print_short_direct(char *data, int index)
{
	ft_printf("%c%d", DIRECT_CHAR, chartoshort(&data[index]));
	return (2);
}

int	print_int_direct(char *data, int index)
{
	ft_printf("%c%d", DIRECT_CHAR, chartoint(&data[index]));
	return (4);
}
