/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 04:11:28 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/10 14:06:29 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

#include <stdlib.h>

int				show_usage(void)
{
	ft_printf("usage: ./diasam <file.cor>\n");
	return (0);
}

int				bad_input(char *message, char *mem)
{
	free(mem);
	ft_printf("%s", message);
	return (0);
}

void			routine(char *data, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while ((size_t)j < sizeof(g_op_tab) / sizeof(t_op))
		{
			if (data[i] == g_op_tab[j].opcode)
			{
				i += print_instruction(&data[i], g_op_tab[j]);
				break ;
			}
			j++;
		}
		if ((size_t)j >= (sizeof(g_op_tab) / sizeof(t_op)) - 1)
		{
			ft_printf("error: unknown mnemonic %#hhx ", data[i]);
			ft_printf("at file offset %#zx\n", (size_t)i + sizeof(t_header));
			break ;
		}
	}
}

int				main(int ac, char **av)
{
	size_t		filesize;
	char		*data;
	t_header	*header;

	if (ac == 2)
	{
		data = getfilecontents(av[1], &filesize);
		header = (t_header *)data;
		if (!check_magic(header))
			return (bad_input("error: header 'magic' is wrong\n", data));
		(void)print_prog_info(header);
		if (sizeof(t_header) + betole(header->prog_size) != filesize)
			return (bad_input("error: bad file size, corrupt file?\n", data));
		(void)routine(&data[sizeof(t_header)], betole(header->prog_size));
		free(data);
	}
	else
		return (show_usage());
	return (0);
}
