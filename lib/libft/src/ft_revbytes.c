/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revbytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 09:24:04 by sgardner          #+#    #+#             */
/*   Updated: 2018/05/03 06:40:34 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_revbytes(void *ptr, size_t n)
{
	size_t	i;
	size_t	half;
	t_byte	*data;
	t_byte	swap;

	i = 0;
	half = n / 2;
	data = (t_byte *)ptr;
	while (i < half)
	{
		swap = data[i];
		data[i] = data[n - i - 1];
		data[n - i - 1] = swap;
		++i;
	}
	return (ptr);
}
