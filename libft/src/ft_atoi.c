/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:04:11 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 17:24:15 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	n;
	int	sign;

	while (IS_SPACE(*s))
		++s;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '-' || *s == '+')
		++s;
	n = 0;
	while (IS_DIGIT(*s))
		n = (n * 10) + ((*s++ - '0') * sign);
	return (n);
}
