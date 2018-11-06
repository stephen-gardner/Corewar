/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 14:55:35 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/14 18:30:49 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conv_n(t_buff *buff, t_arg *arg)
{
	if (F(F_H))
		*(va_arg(buff->ap, char *)) = buff->len;
	else if (F(F_HH))
		*(va_arg(buff->ap, short *)) = buff->len;
	else if (F(F_L))
		*(va_arg(buff->ap, long *)) = buff->len;
	else if (F(F_LL))
		*(va_arg(buff->ap, long long *)) = buff->len;
	else if (F(F_J))
		*(va_arg(buff->ap, intmax_t *)) = buff->len;
	else if (F(F_Z))
		*(va_arg(buff->ap, ssize_t *)) = buff->len;
	else
		*(va_arg(buff->ap, int *)) = buff->len;
}

t_bool	conv_percent(t_buff *buff, t_arg *arg)
{
	char	*str;

	if (!(str = ft_memalloc(1)))
		return (FALSE);
	*str = '%';
	return (add_str(buff, arg, str, 1));
}
