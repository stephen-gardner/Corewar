/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 04:40:47 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/02 02:59:51 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "libftprintf.h"
# include "../op.h"
# include "../instr.h"
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>

# define BUFF_SIZE 1
# define TAB_SIZE 8
# define COMMENT_TABS 4
# define COMMENT_TAB_CHAR ';'
# define MAX_INSTR_BYTES 11
# define BINARY_EXTENSION ".cor"

# define C_RED "\e[0;31m"
# define C_GREEN "\e[0;32m"
# define C_YELLOW "\e[0;33m"
# define C_END "\e[0m"

typedef	struct	s_in
{
	char		*original;
	char		*label;
	char		*i_name;
	char		*i_oper;
	int			type;
	int			opcode;
	int			has_acb;
	int			acb;
	int			short_direct;
	int			arg_count;
	char		**operands;
	int			op_types[MAX_ARGS_NUMBER];
	int			op_values[MAX_ARGS_NUMBER];
	int			size;
	int			address;
	struct s_in	*next;
}				t_in;

typedef t_in	t_instruction;

typedef	struct	s_asm
{
	int			options;
	int			fd;
	int			have_name;
	int			have_comment;
	int			lines;
	int			prog_size;
	char		*filename;
	char		*tmp;
	char		**split;
	t_in		*instruction;
	t_header	header;
	char		body[CHAMP_MAX_SIZE * 2];

}				t_asm;

extern t_op		g_op_tab[17];

bool			is_direct_label(char *str);
bool			is_indirect_label(char *str);
bool			is_label(char *str);
bool			is_valid_operand(char *str);
bool			ft_isspace(int c);
bool			is_direct(char *str);
bool			is_header_complete(t_asm *a);
bool			is_indirect(char *str);
bool			is_instruction(char *str);
bool			is_register(char *str);
bool			is_valid_magic(t_header *header);
bool			string_is_integer(char *str);
bool			string_is_label(char *str);
char			*hexdump_bytes(t_instruction *ptr, int *count);
char			*prepare_output_filename(char *original);
char			*strip_comments(char *str);
char			*trim_left(char *str);
char			*trim_right(char *str);
int				count_matching_chars(char *str, char c);
int				count_operands(char *str);
int				betole(int x);
int				chartoint(char *array);
int				count_char_array(char **array);
int				get_arg_type(char arg_byte, int arg_number);
int				get_operand_type(char *op);
int				init(char **av, int f_index, int opt);
int				main(int ac, char **av);
int				put_file_contents
					(char *filename, unsigned char *data, size_t size);
int				show_usage(void);
int				update_acb(int acb, int index, int op_type);
short			chartoshort(char *array);
t_in			*queue_prepare(t_asm *a, char *name, char *oper);
t_in			*find_label(t_asm *a, char *str);
t_op			find_instruction(char *instruction);
void			add_instruction_to_queue(t_asm *a, char *name, char *oper);
void			add_label_to_queue(t_asm *a, char *label);
void			add_to_queue(t_asm *a, t_in *ptr);
void			append_nl_string(char **parent, char *child);
void			clean_up(t_asm *a);
void			destroy_char_array(char **array, int size);
void			fix_operand_values(t_asm *a, int i, t_instruction *ptr);
void			free_split(char **array);
void			generate_hexdump(t_asm *a);
void			generate_output(t_asm *a);
void			get_mandatory_info(t_asm *a);
void			header_error(char *msg, t_asm *a);
void			hexdump_print(t_instruction *ptr, char *bytes, int count);
void			hexdump_write_operands(t_in *ptr, char *res, int *i, int j);
void			i_fatal(t_asm *a, char **split, char *msg);
void			insert_into_char_array(t_asm *a, char *str);
void			add_operand_size(int type, t_in *ptr, t_op instr);
void			output_write_data(t_asm *a, t_instruction *ptr, int *i, int j);
void			parse_instructions(t_asm *a);
void			print_error(void);
void			process_instruction(t_asm *a);
void			process_whitespace(char *str);
void			resolve_labels(t_asm *a);
void			routine(t_asm *a);
void			string_shift_left(char *str);
void			validate_champion_comment(t_asm *a, int *i);
void			validate_champion_name(t_asm *a, int *i);
void			validate_header_info(t_asm *a);
void			warning(char *str);
void			whitespace_consolidate(char *str);
void			whitespace_transform(char *str);
void			whitespace_trim(char *str);
void			error_invalid_operand(char *line, char *s1, char *s2, t_asm *a);
void			error_bad_operand_count(char *line, t_asm *a);

#endif
