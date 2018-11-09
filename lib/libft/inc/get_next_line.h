/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 13:06:04 by sgardner          #+#    #+#             */
/*   Updated: 2018/11/04 14:19:25 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# define BUFF_SIZE 1

typedef struct	s_file
{
	int				fd;
	size_t			offset;
	char			*buffer;
	struct s_file	*next;
}				t_file;

int				get_next_line(const int fd, char **line);
#endif
