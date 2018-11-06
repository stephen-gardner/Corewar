/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_wchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 22:28:59 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/15 03:53:22 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "ft_printf.h"

static int	utflen(wchar_t *ws, int maxlen)
{
	int		len;
	int		size;

	len = 0;
	while (*ws)
	{
		if (*ws < 0x80)
			size = 1;
		else if (*ws < 0x800)
			size = 2;
		else if (*ws < 0x10000)
			size = 3;
		else if (*ws < 0x110000)
			size = 4;
		else
			return (-1);
		if (len + size > maxlen)
			break ;
		len += size;
		++ws;
	}
	return (len);
}

static void	convert_utf(char *dst, wchar_t *src, int size)
{
	if (size < 2)
		*dst = *src;
	else if (size < 3)
		*dst++ = 0xC0 | (*src >> 6);
	else if (size < 4)
		*dst++ = 0xE0 | (*src >> 12);
	else
		*dst++ = 0xF0 | (*src >> 18);
	while (--size)
		*dst++ = 0x80 | ((*src >> ((size - 1) * 6)) & 0x3F);
}

static void	wctoutf(char *dst, wchar_t *src, int maxlen)
{
	int	len;
	int	size;

	len = 0;
	while (*src)
	{
		if (*src < 0x80)
			size = 1;
		else if (*src < 0x800)
			size = 2;
		else if (*src < 0x10000)
			size = 3;
		else if (*src < 0x110000)
			size = 4;
		else
			break ;
		if (len + size > maxlen)
			break ;
		convert_utf(dst, src++, size);
		dst += size;
		len += size;
	}
}

t_bool		conv_wchar(t_buff *buff, t_arg *arg)
{
	wchar_t	wc[2];
	char	*mbs;
	int		mbs_len;

	wc[0] = (wchar_t)va_arg(buff->ap, wint_t);
	wc[1] = L'\0';
	mbs_len = (wc[0]) ? utflen(wc, sizeof(wchar_t)) : 1;
	if (!(mbs = ft_memalloc(mbs_len)))
		return (FALSE);
	wctoutf(mbs, wc, mbs_len);
	return (add_str(buff, arg, mbs, mbs_len));
}

t_bool		conv_wstr(t_buff *buff, t_arg *arg)
{
	wchar_t	*ws;
	char	*mbs;
	int		mbs_len;

	if (!(ws = va_arg(buff->ap, wchar_t *)))
		ws = L"(null)";
	mbs_len = utflen(ws, (F(F_PRECISE)) ? arg->precision : INT_MAX);
	if (mbs_len < 0 || !(mbs = ft_memalloc(mbs_len)))
		return (FALSE);
	wctoutf(mbs, ws, mbs_len);
	return (add_str(buff, arg, mbs, mbs_len));
}
