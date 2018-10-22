/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_int_deprecated.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 21:49:01 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/15 02:32:56 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	conv_ld_deprecated(t_buff *buff, t_arg *arg)
{
	arg->flags = ((arg->flags >> 7) << 7) | F_L;
	return (add_num(buff, arg, 10, TRUE));
}

t_bool	conv_lo_deprecated(t_buff *buff, t_arg *arg)
{
	arg->flags = ((arg->flags >> 7) << 7) | F_L;
	return (add_num(buff, arg, 8, FALSE));
}

t_bool	conv_lu_deprecated(t_buff *buff, t_arg *arg)
{
	arg->flags = ((arg->flags >> 7) << 7) | F_L;
	return (add_num(buff, arg, 10, FALSE));
}
