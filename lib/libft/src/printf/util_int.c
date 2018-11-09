/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 01:51:54 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/17 19:39:37 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*format_num(t_arg *arg, char *prefix, char *num)
{
	char	*res;
	int		pad;
	int		len;
	int		prefix_len;

	pad = 0;
	len = LEN(num);
	prefix_len = LEN(prefix);
	if (F(F_PRECISE))
	{
		pad = arg->precision - len + (*num == '-');
		if (TO_LOWER(arg->conv) == 'o' && *prefix == '0')
			--pad;
	}
	else if (F(F_ZERO) && !F(F_MINUS))
		pad = arg->width - len - prefix_len;
	if (pad < 0)
		pad = 0;
	if (!(res = ft_memalloc(prefix_len + len + pad + 1)))
		return (NULL);
	ft_memcpy(res, prefix, prefix_len);
	ft_memset(res + prefix_len, '0', pad);
	ft_memcpy(res + prefix_len + pad, num, len);
	return (res);
}

char		*get_prefix(t_arg *arg, char *num, int base)
{
	static char	prefix[3];
	char		conv;

	ft_memset(prefix, 0, 3);
	if (*num == '-')
		return (prefix);
	if (F(F_HASH) && (arg->conv == 'p' || *num != '0'))
	{
		if (base == 16 || base == 8)
			prefix[0] = '0';
		if (base == 16)
			prefix[1] = 'x';
	}
	else if ((conv = TO_LOWER(arg->conv)) == 'd' || conv == 'i' || conv == 'f')
	{
		if (F(F_PLUS))
			*prefix = '+';
		else if (F(F_SPACE))
			*prefix = ' ';
	}
	return (prefix);
}

intmax_t	get_int(t_buff *buff, t_arg *arg)
{
	intmax_t	n;

	n = va_arg(buff->ap, intmax_t);
	if (F(F_H))
		n = (short)n;
	else if (F(F_HH))
		n = (char)n;
	else if (F(F_L))
		n = (long)n;
	else if (F(F_LL))
		n = (long long)n;
	else if (F(F_J))
		;
	else if (F(F_Z))
		n = (ssize_t)n;
	else
		n = (int)n;
	return (n);
}

uintmax_t	get_uint(t_buff *buff, t_arg *arg)
{
	uintmax_t	un;

	un = va_arg(buff->ap, uintmax_t);
	if (F(F_H))
		un = (unsigned short)un;
	else if (F(F_HH))
		un = (unsigned char)un;
	else if (F(F_L))
		un = (unsigned long)un;
	else if (F(F_LL))
		un = (unsigned long long)un;
	else if (F(F_J))
		;
	else if (F(F_Z) || arg->conv == 'p')
		un = (size_t)un;
	else
		un = (unsigned int)un;
	return (un);
}

char		*uitoa(uintmax_t un, int base, t_bool negative)
{
	static char	num[32];
	char		*pos;

	pos = &num[31];
	*pos-- = '\0';
	if (un == 0)
		*pos-- = '0';
	while (un > 0)
	{
		*pos-- = BASE_KEY[un % base];
		un /= base;
	}
	if (negative)
		*pos-- = '-';
	return (++pos);
}
