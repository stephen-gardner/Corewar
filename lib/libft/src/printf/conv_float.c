/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 02:34:13 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/15 04:03:41 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static void	round_fstring(char *num, int base)
{
	char	*end;

	end = num;
	if (*num-- >= BASE_KEY[base / 2])
	{
		while (*num == BASE_KEY[base - 1] || *num == '.')
		{
			if (*num != '.')
				*num = '0';
			--num;
		}
		*num = BASE_KEY[(*num - '0') + 1];
	}
	*end = '\0';
}

static void	load_mantissa(char *num, long double f, int precision, float base)
{
	if (precision == -1)
	{
		*num = BASE_KEY[(int)(f * base)];
		round_fstring(num, (int)base);
	}
	else
	{
		*num++ = '.';
		++precision;
		while (precision--)
		{
			f *= base;
			*num++ = BASE_KEY[(int)f];
			f -= (int)f;
		}
		*num = '\0';
		round_fstring(num - 1, (int)base);
	}
}

static char	*ftoa(long double f, int precision, float base, t_bool negative)
{
	char		*num;
	long double	power;
	int			len;
	int			digit;
	int			i;

	power = 1.0;
	len = 2;
	while (power < f / base && len++)
		power *= base;
	num = ft_memalloc(negative + len + (precision > 0) + precision + 1);
	i = 0;
	if (negative)
		num[i++] = '-';
	while (power > 0.0)
	{
		digit = (int)(f / power);
		num[i++] = BASE_KEY[digit];
		f -= digit * power;
		power = (power != 1.0) ? power / base : 0.0;
	}
	if (!precision)
		--precision;
	load_mantissa(&num[i], f, precision, base);
	return (num);
}

static char	*build_float(t_buff *buff, t_arg *arg)
{
	long double	f;
	char		*num;
	int			precision;

	f = (F(F_LD)) ? va_arg(buff->ap, long double) : va_arg(buff->ap, double);
	precision = (F(F_PRECISE) || arg->precision) ? arg->precision : 6;
	if (f != f)
		num = ft_strdup((IS_UPPER(arg->conv)) ? "NAN" : "nan");
	else if (f == 1.0 / 0.0)
		num = ft_strdup((IS_UPPER(arg->conv)) ? "INF" : "inf");
	else
		num = ftoa((f < 0) ? -f : f, precision, 10.0, f < 0);
	return (num);
}

t_bool		conv_float(t_buff *buff, t_arg *arg)
{
	char	*num;
	char	*prefix;
	char	*res;
	int		len;
	int		prefix_len;

	if (!(num = build_float(buff, arg)))
		return (FALSE);
	len = LEN(num);
	prefix = get_prefix(arg, num, 10);
	if ((prefix_len = LEN(prefix)))
	{
		if (!(res = ft_memalloc(prefix_len + len)))
		{
			free(num);
			return (FALSE);
		}
		ft_memcpy(res, prefix, prefix_len);
		ft_memcpy(res + prefix_len, num, len);
		free(num);
	}
	else
		res = num;
	return (add_str(buff, arg, res, len));
}
