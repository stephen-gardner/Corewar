/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 04:40:47 by asarandi          #+#    #+#             */
/*   Updated: 2018/02/10 14:05:15 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H

# include "../instr.h"
# include "../op.h"

# include <libft.h>
# include <ft_printf.h>

# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>

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
