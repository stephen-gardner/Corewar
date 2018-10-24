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
	main\
	load\
	msg\
	ops\
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

clean:
	@make -C libft $@
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed$(NC)"

fclean: clean
	@make -C libft $@
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed$(NC)"

re: fclean all
