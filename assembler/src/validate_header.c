/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:41:20 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/02 00:41:39 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	validate_champion_name(t_asm *a, int *i)
{
	int		len;
	char	*quote1;
	char	*str;

	str = ft_strdup(a->split[*i]);
	while ((count_matching_chars(str, '"') < 2) && (*i < a->lines - 1))
		append_nl_string(&str, a->split[++*i]);
	if (count_matching_chars(str, '"') > 2)
		return (header_error(".name has too many quote marks (\")", a));
	if (count_matching_chars(str, '"') == 2)
	{
		quote1 = ft_strchr(str, '"') + 1;
		len = ft_strchr(quote1, '"') - quote1;
		if (len < 1)
			warning(".name is blank");
		if (len > PROG_NAME_LENGTH)
			return (header_error(".name length exceeds PROG_NAME_LENGTH", a));
		ft_strncpy(a->header.prog_name, quote1, (int)len);
		a->have_name = 1;
	}
	free(str);
	return ;
}

void	validate_champion_comment(t_asm *a, int *i)
{
	int		len;
	char	*quote1;
	char	*str;

	str = ft_strdup(a->split[*i]);
	while ((count_matching_chars(str, '"') < 2) && (*i < a->lines - 1))
		append_nl_string(&str, a->split[++*i]);
	if (count_matching_chars(str, '"') > 2)
		return (header_error(".comment has too many quote marks (\")", a));
	if (count_matching_chars(str, '"') == 2)
	{
		quote1 = ft_strchr(str, '"') + 1;
		len = ft_strchr(quote1, '"') - quote1;
		if (len < 1)
			warning(".comment is blank");
		if (len > COMMENT_LENGTH)
			return (header_error(".comment length exceeds COMMENT_LENGTH", a));
		ft_strncpy(a->header.comment, quote1, (int)len);
		a->have_comment = 1;
	}
	free(str);
	return ;
}

void	validate_header_info(t_asm *a)
{
	int	len1;
	int len2;
	int i;

	len1 = ft_strlen(NAME_CMD_STRING);
	len2 = ft_strlen(COMMENT_CMD_STRING);
	i = 0;
	while (i < a->lines)
	{
		if ((a->split[i] != NULL) && (a->split[i][0] != 0))
		{
			a->tmp = trim_left(ft_strdup(a->split[i]));
			if (ft_strncmp(a->tmp, NAME_CMD_STRING, len1) == 0)
				validate_champion_name(a, &i);
			if (ft_strncmp(a->tmp, COMMENT_CMD_STRING, len2) == 0)
				validate_champion_comment(a, &i);
			free(a->tmp);
			a->tmp = NULL;
		}
		i++;
	}
	return ;
}

void	get_mandatory_info(t_asm *a)
{
	char	*line;

	while ((!is_header_complete(a)) && (get_next_line(a->fd, &line) > 0))
	{
		insert_into_char_array(a, line);
		if (line != NULL)
		{
			if (line[0] != 0)
				validate_header_info(a);
		}
	}
	if (!is_header_complete(a))
	{
		if (a->have_name == 0)
			header_error("file is missing .name command", a);
		if (a->have_comment == 0)
			header_error("file is missing .comment command", a);
	}
	return ;
}
