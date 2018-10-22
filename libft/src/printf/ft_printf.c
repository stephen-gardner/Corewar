/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 22:42:01 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/15 08:29:58 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"

int	ft_asprintf(char **ret, const char *fmt, ...)
{
	va_list	ap;
	int		len;

	*ret = NULL;
	va_start(ap, fmt);
	len = process(ret, ULONG_MAX, fmt, ap);
	va_end(ap);
	return (len);
}

int	ft_dprintf(int fd, const char *fmt, ...)
{
	va_list	ap;
	char	*out;
	int		len;

	out = NULL;
	va_start(ap, fmt);
	len = process(&out, ULONG_MAX, fmt, ap);
	va_end(ap);
	if (len < 0)
		return (-1);
	len = write(fd, out, len);
	free(out);
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	char	*out;
	int		len;

	out = NULL;
	va_start(ap, fmt);
	len = process(&out, ULONG_MAX, fmt, ap);
	va_end(ap);
	if (len < 0)
		return (-1);
	len = write(STDOUT_FILENO, out, len);
	free(out);
	return (len);
}

int	ft_snprintf(char *str, size_t size, const char *fmt, ...)
{
	va_list	ap;
	int		len;

	if (!str)
		return (-1);
	va_start(ap, fmt);
	len = process(&str, size, fmt, ap);
	va_end(ap);
	return (len);
}

int	ft_sprintf(char *str, const char *fmt, ...)
{
	va_list	ap;
	int		len;

	if (!str)
		return (-1);
	va_start(ap, fmt);
	len = process(&str, INT_MAX, fmt, ap);
	va_end(ap);
	return (len);
}
