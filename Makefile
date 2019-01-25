#!/usr/bin/make -f

UNAME = $(shell uname -s)

################################################################################
# SETTINGS                                                                     #
################################################################################


# [ COMPILATION ]

CC = gcc
CFLAGS += -Wall -Werror -Wextra
CFLAGS += -Ofast -funroll-loops
CFLAGS += #-g -fsanitize=address
ifeq ($(UNAME),Linux)
	CFLAGS += -Wno-unused-result
endif
OBJ_DIR = obj

# [ LIBRARIES ]

LIB = lib
LIBFT_DIR = $(LIB)/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I $(LIBFT_DIR)/inc

ifeq ($(UNAME),Linux)
	GFX_FRAMEWORK = -lX11 -lXext -lbsd -lm
	MLX_DIR = $(LIB)/libmlx/linux
	MLX_INC = -I $(MLX_DIR)/inc
endif
ifeq ($(UNAME),Darwin)
	GFX_FRAMEWORK = -framework OpenGL -framework AppKit
	MLX_DIR = $(LIB)/libmlx/macos
	MLX_INC = -I $(MLX_DIR)/inc
endif
LIBMLX = $(MLX_DIR)/libmlx.a

RVM_DIR = $(LIB)/refvm
RVM_INC = -I $(RVM_DIR)/inc
RVM_SRC_DIR = $(RVM_DIR)/src
RVM_SRC = \
	zaz_op
RVM_OBJ_DIR = $(OBJ_DIR)/$(RVM_DIR)
RVM_OBJ = $(patsubst %, $(RVM_OBJ_DIR)/%.o, $(RVM_SRC))

# [ ASSEMBLER ]

ASM = asm
ASM_DIR = assembler
ASM_INC = -I $(ASM_DIR)/inc $(RVM_INC) $(LIBFT_INC)
ASM_SRC_DIR = $(ASM_DIR)/src
ASM_SRC = \
	char_array\
	count\
	error\
	file_op\
	header_utils\
	hexdump\
	instruction_utils\
	instructions\
	is_operand\
	label_utils\
	main\
	operand_error\
	output\
	queue_add\
	resolve_labels\
	string\
	trim\
	util\
	validate_header\
	whitespace
ASM_OBJ_DIR = $(OBJ_DIR)/$(ASM_DIR)
ASM_OBJ = $(patsubst %, $(ASM_OBJ_DIR)/%.o, $(ASM_SRC))

# [ DISASSEMBLER ]

DISASM = disasm
DISASM_DIR = disassembler
DISASM_INC = -I $(DISASM_DIR)/inc $(RVM_INC) $(LIBFT_INC)
DISASM_SRC_DIR = $(DISASM_DIR)/src
DISASM_SRC = \
	file_op\
	instruction\
	main\
	print\
	stdin\
	util
DISASM_OBJ_DIR = $(OBJ_DIR)/$(DISASM_DIR)
DISASM_OBJ = $(patsubst %, $(DISASM_OBJ_DIR)/%.o, $(DISASM_SRC))

# [ VIRTUAL MACHINE ]

VM = corewar
VM_DIR = vm
VM_INC = -I $(VM_DIR)/inc $(MLX_INC) $(LIBFT_INC)
ifeq ($(UNAME),Linux)
	VM_INC += -I $(VM_DIR)/inc/linux
endif
ifeq ($(UNAME),Darwin)
	VM_INC += -I $(VM_DIR)/inc/macos
endif
VM_SRC_DIR = $(VM_DIR)/src
VM_SRC = \
	champ\
	coreio\
	execution\
	gui/gui_bars\
	gui/gui_blocks\
	gui/gui_colors\
	gui/gui_cpf\
	gui/gui_hooks\
	gui/gui_loop\
	gui/gui_main
ifeq ($(UNAME),Linux)
	VM_SRC += gui/gui_mlx_linux
endif
ifeq ($(UNAME),Darwin)
	VM_SRC += gui/gui_mlx_macos
endif
VM_SRC += \
	gui/gui_pc_boxes\
	gui/gui_text\
	main\
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
	process
VM_OBJ_DIR = $(OBJ_DIR)/$(VM_DIR)
VM_OBJ = $(patsubst %, $(VM_OBJ_DIR)/%.o, $(VM_SRC))

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

all: $(ASM) $(DISASM) $(VM)

# [ LINKING ]

$(ASM): $(LIBFT) $(ASM_OBJ) $(RVM_OBJ)
	@printf "$(YELLOW)%-$(COLSIZE)s$(NC)" "Building $@... "
	@$(CC) $(CFLAGS) $(LIBFT) $(ASM_OBJ) $(RVM_OBJ) -o $@
	@echo "$(GREEN)DONE$(NC)"

$(DISASM): $(LIBFT) $(DISASM_OBJ) $(RVM_OBJ)
	@printf "$(YELLOW)%-$(COLSIZE)s$(NC)" "Building $@... "
	@$(CC) $(CFLAGS) $(LIBFT) $(DISASM_OBJ) $(RVM_OBJ) -o $@
	@echo "$(GREEN)DONE$(NC)"

$(VM): $(LIBFT) $(LIBMLX) $(VM_OBJ)
	@printf "$(YELLOW)%-$(COLSIZE)s$(NC)" "Building $@... "
	@$(CC) $(CFLAGS) $(GFX_FRAMEWORK) $(LIBFT) $(LIBMLX) $(VM_OBJ) -o $@
	@echo "$(GREEN)DONE$(NC)"

# [ COMPILING ]

$(ASM_OBJ_DIR)/%.o: $(ASM_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " > Compiling $<..."
	@$(CC) $(CFLAGS) $(ASM_INC) -c $< -o $@

$(DISASM_OBJ_DIR)/%.o: $(DISASM_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " > Compiling $<..."
	@$(CC) $(CFLAGS) $(DISASM_INC) -c $< -o $@

$(VM_OBJ_DIR)/%.o: $(VM_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " > Compiling $<..."
	@$(CC) $(CFLAGS) $(VM_INC) -c $< -o $@

# [ LIBRARIES ]

$(LIBFT):
	@printf "$(YELLOW)%-$(COLSIZE)s$(NC)" "Building $@... "
	@make -C $(LIBFT_DIR)

$(LIBMLX):
	@printf "$(YELLOW)%-$(COLSIZE)s$(NC)" "Building $@... " 
	@make -C $(MLX_DIR)

$(RVM_OBJ_DIR)/%.o: $(RVM_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " > Compiling $<..."
	@$(CC) $(CFLAGS) $(ASM_INC) $(RVM_INC) -c $< -o $@

# [ CLEANING ]

again:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed"
	@rm -f $(ASM)
	@echo "$(ASM) removed"
	@rm -f $(DISASM)
	@echo "$(DISASM) removed"
	@rm -f $(VM)
	@echo "$(VM) removed$(NC)"
	@make

clean:
	@make -C $(LIBFT_DIR) $@
	@make -C $(MLX_DIR) $@
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed$(NC)"

fclean: clean
	@make -C $(LIBFT_DIR) $@
	@make -C $(MLX_DIR) $@
	@rm -f $(ASM)
	@echo "$(RED)$(ASM) removed"
	@rm -f $(DISASM)
	@echo "$(DISASM) removed"
	@rm -f $(VM)
	@echo "$(VM) removed$(NC)"

re: fclean all
