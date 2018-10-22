/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 07:50:03 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 16:33:53 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	num[12];
	int		sign;
	int		digit;

	num[11] = '\0';
	sign = (n < 0) ? -1 : 1;
	digit = 10;
	if (!n)
		num[digit--] = '0';
	while (n != 0)
	{
		num[digit--] = (char)(((n % 10) * sign) + '0');
		n /= 10;
	}
	if (sign < 0)
		num[digit--] = '-';
	return (ft_strdup(&num[++digit]));
}
