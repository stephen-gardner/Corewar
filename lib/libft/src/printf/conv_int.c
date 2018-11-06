/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 21:36:27 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/15 00:22:50 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	conv_d(t_buff *buff, t_arg *arg)
{
	return (add_num(buff, arg, 10, TRUE));
}

t_bool	conv_o(t_buff *buff, t_arg *arg)
{
	return (add_num(buff, arg, 8, FALSE));
}

t_bool	conv_p(t_buff *buff, t_arg *arg)
{
	arg->flags |= F_HASH;
	return (add_num(buff, arg, 16, FALSE));
}

t_bool	conv_u(t_buff *buff, t_arg *arg)
{
	return (add_num(buff, arg, 10, FALSE));
}

t_bool	conv_x(t_buff *buff, t_arg *arg)
{
	return (add_num(buff, arg, 16, FALSE));
}
