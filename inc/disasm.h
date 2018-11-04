/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 04:40:47 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/04 14:37:38 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H

# include "zaz_op.h"

# include "libft.h"
# include "ft_printf.h"

# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>

typedef struct	s_op
{
	char		*name;
	int			arg_count;
	t_arg_type	arg[MAX_ARGS_NUMBER];
	char		opcode;
	int			cycles;
	char		*description;
	int			needs_acb;
	int			short_direct;
}				t_op;

extern t_op		g_op_tab[17];

char			*stdin_read_eof(size_t *count);
int				put_file_contents
					(char *filename, unsigned char *data, size_t size);
int				bad_input(char *message, char *mem);
int				betole(int	x);
int				chartoint(char *array);
int				check_magic(t_header *header);
int				complex_instruction(char *data, t_op op);
int				get_arg_type(char arg_byte, int arg_number);
int				print_ind(char *data, int index);
int				print_instruction(char	*data, t_op op);
int				print_int_direct(char *data, int index);
int				print_prog_info(t_header *header);
int				print_register(char *data, int index);
int				print_short_direct(char *data, int index);
int				show_usage(void);
int				main(int ac, char **av);
short			chartoshort(char *array);
ssize_t			getfilesize(char *filename);
void			*getfilecontents(char *filename, size_t *size);
void			quit(int errnum, void *memory);
void			routine(char *data, int size);
void			stdin_quit(char *membuf);

#endif
