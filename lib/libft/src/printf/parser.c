/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 20:21:03 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/15 01:13:22 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_flags(t_buff *buff, t_arg *arg, const char *fmt)
{
	int	n;

	n = 0;
	while (fmt[n])
	{
		if (fmt[n] == '-')
			arg->flags |= F_MINUS;
		else if (fmt[n] == '+')
			arg->flags |= F_PLUS;
		else if (fmt[n] == ' ')
			arg->flags |= F_SPACE;
		else if (fmt[n] == '0')
			arg->flags |= F_ZERO;
		else if (fmt[n] == '#')
			arg->flags |= F_HASH;
		else if (fmt[n] == '&')
		{
			arg->flags |= F_ESCAPE;
			arg->esc = va_arg(buff->ap, char *);
		}
		else
			break ;
		++n;
	}
	return (n);
}

static int	find_length(t_arg *arg, const char *fmt)
{
	if (*fmt == 'h' && *(fmt + 1) == 'h')
	{
		arg->flags |= F_HH;
		return (2);
	}
	else if (*fmt == 'l' && *(fmt + 1) == 'l')
	{
		arg->flags |= F_LL;
		return (2);
	}
	else if (*fmt == 'h')
		arg->flags |= F_H;
	else if (*fmt == 'L')
		arg->flags |= F_LD;
	else if (*fmt == 'l')
		arg->flags |= F_L;
	else if (*fmt == 'j')
		arg->flags |= F_J;
	else if (*fmt == 'z')
		arg->flags |= F_Z;
	else
		return (0);
	return (1);
}

static int	find_precision(t_buff *buff, t_arg *arg, const char *fmt)
{
	int	n;

	if (*fmt != '.')
		return (0);
	arg->flags |= F_PRECISE;
	if (*(++fmt) == '*')
	{
		if ((arg->precision = va_arg(buff->ap, int)) < 0)
		{
			arg->flags ^= F_PRECISE;
			arg->precision = 0;
		}
		return (2);
	}
	n = 0;
	while (fmt[n] && IS_DIGIT(fmt[n]))
		arg->precision = (arg->precision * 10) + (fmt[n++] - '0');
	return (1 + n);
}

static int	find_width(t_buff *buff, t_arg *arg, const char *fmt)
{
	int	n;

	if (*fmt == '*')
	{
		if ((arg->width = va_arg(buff->ap, int)) < 0)
		{
			arg->flags |= F_MINUS;
			arg->width *= -1;
		}
		return (1);
	}
	n = 0;
	while (fmt[n] && IS_DIGIT(fmt[n]))
		arg->width = (arg->width * 10) + (fmt[n++] - '0');
	return (n);
}

t_bool		parse_conv(t_buff *buff, const char **fmt)
{
	t_arg	arg;

	ft_memset(&arg, 0, sizeof(t_arg));
	*fmt += find_flags(buff, &arg, *fmt);
	*fmt += find_width(buff, &arg, *fmt);
	*fmt += find_precision(buff, &arg, *fmt);
	*fmt += find_length(&arg, *fmt);
	arg.conv = **fmt;
	++(*fmt);
	if (arg.conv == 'n')
	{
		conv_n(buff, &arg);
		return (TRUE);
	}
	return (build_arg(buff, &arg));
}
