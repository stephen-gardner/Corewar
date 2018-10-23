/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 04:32:22 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/23 05:23:12 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ft_printf.h"
#include <stdlib.h>

t_bool	error(const char *fmt, ...)
{
	char	*msg;
	va_list	ap;

	va_start(ap, fmt);
	if (vasprintf(&msg, fmt, ap))
	{
		ft_dprintf(2, "%&s %s\n", "31m", "Error:", msg);
		free(msg);
	}
	va_end(ap);
	return (FALSE);
}
