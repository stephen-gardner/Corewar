#!/usr/bin/make -f

################################################################################
# SETTINGS                                                                     #
################################################################################

NAME = corewar
CC = gcc
CFLAGS += -Wall -Werror -Wextra
CFLAGS += -Wno-unused-parameter -Wno-unused-result
CFLAGS += #-Ofast -funroll-loops
CFLAGS += -g -fsanitize=address
INC = -I inc -I libft/inc
LIBFT = libft/libft.a
SRC_DIR = src
OBJ_DIR = obj

ASM_FILES = char_array count error file_op header_utils hexdump instruction_utils instructions is_operand label_utils main operand_error output queue_add resolve_labels string trim util validate_header whitespace zaz_op
ASM_OBJECTS = $(addprefix obj/asm/, $(addsuffix .o, $(ASM_FILES)))
ASM = asm

DISASM_FILES = file_op instruction main print stdin util zaz_op
DISASM_OBJECTS = $(addprefix obj/disasm/, $(addsuffix .o, $(DISASM_FILES)))
DISASM = disasm

UNAME	:= $(shell uname -s)

ifeq ($(UNAME),Linux)
	MLXDIR = libmlx/minilibx_linux/
	MLXINC = -I $(MLX) -I inc/linux
	MLXLIB = -L $(MLX) -lmlx -lXext -lX11 -lm
endif

ifeq ($(UNAME),Darwin)
	MLXDIR = libmlx/minilibx_macos/
	MLXINC = -I $(MLXDIR) -I inc/macos
	MLXLIB = -L $(MLXDIR) -lmlx -framework OpenGL -framework AppKit
endif


SRC = \
	coreio\
	main\
	load\
	msg\
	ops\
	ops/op_add\
	ops/op_aff\
	ops/op_and\
	ops/op_fork\
	ops/op_ld\
	ops/op_ldi\
	ops/op_lfork\
	ops/op_live\
	ops/op_lld\
	ops/op_lldi\
	ops/op_nop\
	ops/op_or\
	ops/op_st\
	ops/op_sti\
	ops/op_sub\
	ops/op_xor\
	ops/op_zjmp\
	process\
	corewar_gui


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

all: $(NAME) $(ASM) $(DISASM)

$(NAME): $(LIBFT) $(OBJ)
	@make -C $(MLXDIR)
	@printf "$(YELLOW)%-$(COLSIZE)s$(NC)" "Building $@... "
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIB) $(MLXLIB) -o $@
	@echo "$(GREEN)DONE$(NC)"

$(LIBFT):
	@printf "$(YELLOW)%-$(COLSIZE)s$(NC)" "Building $@... "
	@make -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " > Compiling $<..."
	@$(CC) $(CFLAGS) $(INC) $(MLXINC) -c $< -o $@

$(DISASM): $(DISASM_OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(INC) $(LIB) $^ -o $@

$(DISASM_OBJECTS): obj/disasm/%.o : src/disasm/%.c | disasmobjdir
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

disasmobjdir: objdir
	mkdir -p obj/disasm

$(ASM): $(ASM_OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(INC) $(LIB) $^ -o $@

$(ASM_OBJECTS): obj/asm/%.o : src/asm/%.c | asmobjdir
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

asmobjdir: objdir
	mkdir -p obj/asm/

objdir:
	mkdir -p obj/

again:
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed"
	@echo "$(NAME) removed$(NC)"
	@make

clean:
	@make clean -C $(MLXDIR)
	@make -C libft $@
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed$(NC)"

rmchamps:
	find . -iname "*.cor" -exec rm {} \;

fclean: clean
	@make -C libft $@
	@rm -f $(NAME) $(ASM) $(DISASM)
	@echo "$(RED)$(NAME) removed$(NC)"

re: fclean all
