/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 23:05:57 by sgardner          #+#    #+#             */
/*   Updated: 2018/07/10 02:58:05 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

const t_conv	g_disp[] = {
	{ '%', conv_percent },
	{ 'C', conv_wchar },
	{ 'c', conv_char },
	{ 'D', conv_ld_deprecated },
	{ 'd', conv_d },
	{ 'F', conv_float },
	{ 'f', conv_float },
	{ 'i', conv_d },
	{ 'O', conv_lo_deprecated },
	{ 'o', conv_o },
	{ 'p', conv_p },
	{ 'S', conv_wstr },
	{ 's', conv_str },
	{ 'U', conv_lu_deprecated },
	{ 'u', conv_u },
	{ 'X', conv_x },
	{ 'x', conv_x }
};
const int		g_disp_count = sizeof(g_disp) / sizeof(t_conv);

static t_bool	dispatch(t_buff *buff, t_arg *arg)
{
	t_conv	disp;
	int		i;

	i = 0;
	while (i < g_disp_count)
	{
		disp = g_disp[i++];
		if (arg->conv == disp.specifier)
			return (disp.handle(buff, arg));
	}
	return (FALSE);
}

t_bool			build_arg(t_buff *buff, t_arg *arg)
{
	char	*fmt;
	int		len;
	t_bool	res;

	if (F(F_ESCAPE))
	{
		len = LEN(arg->esc);
		if (!(fmt = ft_mlalloc(buff->mchain, len + 2)))
			return (FALSE);
		ft_stpncpy(ft_stpncpy(fmt, "\x1B[", 2), arg->esc, len);
		buff->len += len + 2;
	}
	if (!(res = dispatch(buff, arg)))
		return (FALSE);
	if (F(F_ESCAPE))
	{
		if (!(fmt = ft_mlalloc(buff->mchain, 4)))
			return (FALSE);
		ft_stpncpy(fmt, "\x1B[0m", 4);
		buff->len += 4;
	}
	return (TRUE);
}

static t_bool	build_buffer(t_buff *buff, const char *fmt)
{
	int	n;

	while (*fmt)
	{
		n = 0;
		while (fmt[n] && fmt[n] != '%')
			++n;
		if (!ft_mladd(buff->mchain, (void *)fmt, n | NOFREE))
			return (FALSE);
		fmt += n;
		buff->len += n;
		if (*fmt == '%')
		{
			++fmt;
			if (!parse_conv(buff, &fmt))
				return (FALSE);
		}
	}
	return (TRUE);
}

static t_bool	write_buffer(char **ret, size_t size, t_mchain *mchain)
{
	t_mlink	*mlink;
	char	*tmp;
	size_t	len;

	if (!*ret && !(*ret = ft_memalloc(size + 1)))
		return (FALSE);
	tmp = *ret;
	mlink = ft_mlrev(mchain);
	while (mlink && size)
	{
		if ((len = MLSIZE(mlink)) > size)
			len = size;
		ft_memcpy(tmp, mlink->ptr, len);
		mlink = ft_mlpop(mchain);
		tmp += len;
		size -= len;
	}
	*tmp = '\0';
	return (TRUE);
}

int				process(char **ret, size_t size, const char *fmt, va_list ap)
{
	t_buff		buff;

	ft_memset(&buff, 0, sizeof(t_buff));
	va_copy(buff.ap, ap);
	if (!(buff.mchain = ft_mcget("_ft_printf")) || !build_buffer(&buff, fmt))
	{
		va_end(buff.ap);
		ft_mcdel(buff.mchain);
		return (-1);
	}
	if (size > buff.len)
		size = buff.len;
	if (!write_buffer(ret, size, buff.mchain))
	{
		va_end(buff.ap);
		ft_mcdel(buff.mchain);
		return (-1);
	}
	va_end(buff.ap);
	return (buff.len);
}
