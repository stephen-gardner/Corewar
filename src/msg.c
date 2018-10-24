/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 04:32:22 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/24 00:48:07 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ft_printf.h"
#include <stdlib.h>

const char	*g_errmsg[6] = {
	"%s",
	"%s: %s",
	"%s: exceeds max champion size (%u > %u)",
	"%s: too small to be a champion",
	"%s: invalid header",
	"%s: code size does not match size specified in header"
};

void		dump(t_core *core)
{
	int	i;
	int	line;

	i = 0;
	line = 0;
	ft_printf("0x0000: ");
	while (i < MEM_SIZE)
	{
		if (++line == 32)
		{
			line = 0;
			ft_printf("%.2x\n", core->arena[i++]);
			if (i < MEM_SIZE)
				ft_printf("%#.4x: ", i);
			continue ;
		}
		ft_printf("%.2x ", core->arena[i++]);
	}
}

void		error(int id, ...)
{
	char	*msg;
	va_list	ap;

	va_start(ap, id);
	if (vasprintf(&msg, g_errmsg[id], ap))
	{
		ft_dprintf(2, "%&s %s\n", "31m", "Error:", msg);
		free(msg);
	}
	va_end(ap);
	exit(EXIT_FAILURE);
}
