/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 21:01:24 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/02 02:57:11 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		i_fatal(t_asm *a, char **split, char *msg)
{
	ft_printf(C_YELLOW"LINE %d:"C_END" %s\n", a->lines, a->split[a->lines - 1]);
	ft_printf(C_RED"ERROR:"C_END" %s\n", msg);
	free_split(split);
	clean_up(a);
	exit(0);
}

void		process_instruction(t_asm *a)
{
	char	**split;
	int		count;

	split = ft_strsplit(a->tmp, ' ');
	count = count_char_array(split);
	if ((count == 1) || (count == 3))
	{
		if (!is_label(split[0]))
			i_fatal(a, split, "expecting label");
		else
			add_label_to_queue(a, split[0]);
	}
	if ((count == 2) || (count == 3))
	{
		if (!is_instruction(split[count - 2]))
			i_fatal(a, split, "expecting instruction");
		else if (!is_valid_operand(split[count - 1]))
			i_fatal(a, split, "expecting operands");
		else
			add_instruction_to_queue(a, split[count - 2], split[count - 1]);
	}
	free_split(split);
	return ;
}

static void	string_prepare(char *line, t_asm *a)
{
	if (a->tmp != NULL)
		free(a->tmp);
	a->tmp = ft_strdup(line);
	a->tmp = strip_comments(a->tmp);
	a->tmp = trim_left(a->tmp);
	a->tmp = trim_right(a->tmp);
	return ;
}

void		parse_instructions(t_asm *a)
{
	char	*line;

	while (get_next_line(a->fd, &line) > 0)
	{
		insert_into_char_array(a, line);
		if (line != NULL)
		{
			string_prepare(line, a);
			if (a->tmp[0] != 0)
			{
				process_whitespace(a->tmp);
				process_instruction(a);
			}
			free(a->tmp);
			a->tmp = NULL;
		}
	}
	return ;
}
