/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 04:11:28 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/02 02:39:28 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		show_usage(void)
{
	ft_printf("usage: ./asm [-a] <filename.s>\n\n");
	ft_printf("\toptions:\n");
	ft_printf("\t-a\toutput stripped version w/ hexdump opcodes\n");
	return (0);
}

char	*prepare_output_filename(char *original)
{
	int		i;
	char	*output_file;

	i = ft_strlen(original);
	output_file = ft_memalloc(i + ft_strlen(BINARY_EXTENSION) + 1);
	ft_strcpy(output_file, original);
	while (--i > 0)
	{
		if ((output_file[i] == '.') || (output_file[i] == '/'))
			break ;
	}
	if (output_file[i] != '.')
		i = ft_strlen(output_file);
	ft_strcpy(&output_file[i], BINARY_EXTENSION);
	return (output_file);
}

void	routine(t_asm *a)
{
	char	*of;

	get_mandatory_info(a);
	parse_instructions(a);
	resolve_labels(a);
	if (a->prog_size > CHAMP_MAX_SIZE)
	{
		ft_printf(C_YELLOW"WARNING:"C_END" prog size (%d) ", a->prog_size);
		ft_printf("exceeds CHAMP_MAX_SIZE (%d)\n", CHAMP_MAX_SIZE);
	}
	generate_output(a);
	if (a->options == 1)
		generate_hexdump(a);
	else
	{
		of = prepare_output_filename(a->filename);
		ft_printf(C_GREEN"SUCCESS:"C_END" writing output program to %s\n", of);
		if ((put_file_contents(of, (unsigned char *)&a->header,
				sizeof(t_header) + a->prog_size)) != 1)
			(void)print_error();
		free(of);
	}
}

int		init(char **av, int f_index, int opt)
{
	int		fd;
	t_asm	*a;

	if ((fd = open(av[f_index], O_RDONLY)) == -1)
	{
		ft_printf(C_RED"ERROR:"C_END" '%s' %s\n",
				av[f_index], strerror(errno));
		return (0);
	}
	a = ft_memalloc(sizeof(t_asm));
	a->options = opt;
	a->fd = fd;
	a->filename = av[f_index];
	routine(a);
	clean_up(a);
	return (0);
}

int		main(int ac, char **av)
{
	if (ac == 2)
		init(av, 1, 0);
	else if (ac == 3)
	{
		if (ft_strcmp(av[1], "-a") == 0)
			init(av, 2, 1);
		else
			return (show_usage());
	}
	else
		return (show_usage());
	return (0);
}
