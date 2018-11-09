/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 04:37:34 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/25 05:22:07 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"

int	ft_vasprintf(char **ret, const char *fmt, va_list ap)
{
	*ret = NULL;
	return (process(ret, ULONG_MAX, fmt, ap));
}

int	ft_vdprintf(int fd, const char *fmt, va_list ap)
{
	char	*out;
	int		len;

	out = NULL;
	len = process(&out, ULONG_MAX, fmt, ap);
	if (len < 0)
		return (-1);
	len = write(fd, out, len);
	free(out);
	return (len);
}

int	ft_vprintf(const char *fmt, va_list ap)
{
	char	*out;
	int		len;

	out = NULL;
	len = process(&out, ULONG_MAX, fmt, ap);
	if (len < 0)
		return (-1);
	len = write(STDOUT_FILENO, out, len);
	free(out);
	return (len);
}

int	ft_vsnprintf(char *str, size_t size, const char *fmt, va_list ap)
{
	if (!str)
		return (-1);
	return (process(&str, size, fmt, ap));
}

int	ft_vsprintf(char *str, const char *fmt, va_list ap)
{
	if (!str)
		return (-1);
	return (process(&str, INT_MAX, fmt, ap));
}
