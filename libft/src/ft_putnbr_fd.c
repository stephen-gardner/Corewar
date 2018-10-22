/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 03:30:12 by sgardner          #+#    #+#             */
/*   Updated: 2018/03/19 16:37:04 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
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
	ft_putstr_fd(&num[++digit], fd);
}
