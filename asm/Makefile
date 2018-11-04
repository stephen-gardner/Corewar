NAME	= asm
SRC		= char_array.c count.c error.c file_op.c instruction_utils.c instructions.c is_operand.c label_utils.c main.c op.c output.c queue_add.c resolve_labels.c string.c trim.c util.c validate_header.c whitespace.c header_utils.c hexdump.c operand_error.c
OBJ		= $(SRC:%.c=%.o)
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
DFLAGS	= -g
DNAME	= debug
INC		= -I ../../includes
LIB		= -L../../libft -lft

all:	$(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(INC) -c $(SRC)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

debug:	fclean
	$(CC) $(DFLAGS) $(INC) -c $(SRC)
	$(CC) $(DFLAGS) $(OBJ) $(LIB) -o $(DNAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME) $(DNAME)

re:	fclean all
