/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 01:33:57 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/02 01:08:32 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool	ft_isspace(int c)
{
	if ((c >= 0x09) && (c <= 0x0d))
		return (true);
	else if (c == 0x20)
		return (true);
	else
		return (false);
}

bool	is_header_complete(t_asm *a)
{
	if ((a->have_name == true) && (a->have_comment == true))
		return (true);
	return (false);
}

void	warning(char *str)
{
	ft_printf(C_YELLOW"WARNING:"C_END" %s\n", str);
	return ;
}

void	append_nl_string(char **parent, char *child)
{
	char	*tmp;
	int		len;

	len = ft_strlen(*parent) + ft_strlen(child);
	tmp = ft_memalloc(len + 3);
	ft_strcpy(tmp, *parent);
	ft_strcpy(&tmp[ft_strlen(*parent)], "\n");
	ft_strcpy(&tmp[ft_strlen(*parent) + 1], child);
	free(*parent);
	*parent = tmp;
	return ;
}
