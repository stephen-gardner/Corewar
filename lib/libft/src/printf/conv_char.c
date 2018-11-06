/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 19:02:57 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/27 21:10:09 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

t_bool	conv_char(t_buff *buff, t_arg *arg)
{
	char	*cstr;
	char	c;

	if (F(F_L))
		return (conv_wchar(buff, arg));
	c = (char)va_arg(buff->ap, int);
	if (!(cstr = ft_memalloc(1)))
		return (FALSE);
	*cstr = c;
	return (add_str(buff, arg, cstr, 1));
}

t_bool	conv_str(t_buff *buff, t_arg *arg)
{
	char	*str;
	char	*out;
	int		len;

	if (F(F_L))
		return (conv_wstr(buff, arg));
	if (!(str = va_arg(buff->ap, char *)))
		str = "(null)";
	len = (F(F_PRECISE)) ? NLEN(str, arg->precision) : LEN(str);
	if (!(out = ft_memalloc(len)))
		return (FALSE);
	ft_memcpy(out, str, len);
	return (add_str(buff, arg, out, len));
}
