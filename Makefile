#!/usr/bin/make -f

################################################################################
# SETTINGS                                                                     #
################################################################################

NAME = corewar
CC = gcc
CFLAGS += -Wall -Werror -Wextra
CFLAGS += #-Ofast -funroll-loops
CFLAGS += -g -fsanitize=address
INC = -I inc -I libft/inc
LIBFT = libft/libft.a
SRC_DIR = src
OBJ_DIR = obj

SRC = \
	coreio\
	main\
	load\
	msg\
	ops\
	ops/op_add\
	ops/op_and\
	ops/op_fork\
	ops/op_ld\
	ops/op_ldi\
	ops/op_live\
	ops/op_or\
	ops/op_st\
	ops/op_sti\
	ops/op_sub\
	ops/op_xor\
	ops/op_zjmp\
	process

OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC))

################################################################################
# COLORS                                                                       #
################################################################################

COLSIZE = 50
NC = \033[0m
GREEN = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m

################################################################################
# RULES                                                                        #
################################################################################

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@printf "$(YELLOW)%-$(COLSIZE)s$(NC)" "Building $@... "
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@
	@echo "$(GREEN)DONE$(NC)"

$(LIBFT):
	@printf "$(YELLOW)%-$(COLSIZE)s$(NC)" "Building $@... "
	@make -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " > Compiling $<..."
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

again:
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed"
	@echo "$(NAME) removed$(NC)"
	@make

clean:
	@make -C libft $@
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed$(NC)"

fclean: clean
	@make -C libft $@
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed$(NC)"

re: fclean all
