/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 03:09:52 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/17 19:25:32 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static char		*fix_negative(char *num)
{
	char	*pos;

	pos = ft_strchr(num, '-');
	if (pos && pos != num)
	{
		*pos = *num;
		*num = '-';
	}
	return (num);
}

static char		*build_num(t_buff *buff, t_arg *arg, int base, t_bool is_signed)
{
	char		*num;
	intmax_t	n;
	uintmax_t	un;

	if (is_signed)
	{
		n = get_int(buff, arg);
		if (!n && F(F_PRECISE) && !arg->precision)
			return (ft_strdup(""));
		num = uitoa(ABS(n), base, n < 0);
	}
	else
	{
		un = get_uint(buff, arg);
		if (!un && F(F_PRECISE) && !arg->precision
			&& (!F(F_HASH) || TO_LOWER(arg->conv) == 'x'))
			return (ft_strdup(""));
		num = uitoa(un, base, FALSE);
	}
	num = fix_negative(format_num(arg, get_prefix(arg, num, base), num));
	return (num);
}

static t_bool	add_pad(t_mchain *mchain, int size, char c)
{
	char	*pad;

	if (size < 1)
		return (TRUE);
	if (!(pad = ft_mlalloc(mchain, size)))
		return (FALSE);
	ft_memset(pad, c, size);
	return (TRUE);
}

t_bool			add_num(t_buff *buff, t_arg *arg, int base, t_bool is_signed)
{
	char	*num;
	int		pad;
	int		len;

	if (!(num = build_num(buff, arg, base, is_signed)))
		return (FALSE);
	len = LEN(num);
	pad = arg->width - len;
	if (!F(F_MINUS)
		&& (F(F_PRECISE) || !F(F_ZERO))
		&& !add_pad(buff->mchain, pad, ' '))
	{
		free(num);
		return (FALSE);
	}
	if (arg->conv == 'X')
		ft_strupcase(num);
	if (!ft_mladd(buff->mchain, num, len)
		|| (F(F_MINUS) && !add_pad(buff->mchain, pad, ' ')))
	{
		free(num);
		return (FALSE);
	}
	buff->len += len + ((pad > 0) ? pad : 0);
	return (TRUE);
}

t_bool			add_str(t_buff *buff, t_arg *arg, char *str, int len)
{
	int	pad;

	pad = arg->width - len;
	if (F(F_MINUS))
	{
		if (!ft_mladd(buff->mchain, str, len)
			|| !add_pad(buff->mchain, pad, ' '))
		{
			free(str);
			return (FALSE);
		}
	}
	else
	{
		if (!add_pad(buff->mchain, pad, ' ')
			|| !ft_mladd(buff->mchain, str, len))
		{
			free(str);
			return (FALSE);
		}
	}
	buff->len += len;
	if (pad > 0)
		buff->len += pad;
	return (TRUE);
}
