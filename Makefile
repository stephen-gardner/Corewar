#!/usr/bin/make -f

################################################################################
# SETTINGS                                                                     #
################################################################################

NAME = corewar
CC = gcc
CFLAGS += -Wall -Werror -Wextra
#CFLAGS += -Wno-unused-parameter -Wno-unused-result
#CFLAGS += -Ofast -funroll-loops
#CFLAGS += -g -fsanitize=address
INC = -I inc -I libft/inc
LIBFT = libft/libft.a
SRC_DIR = src/
OBJ_DIR = obj/

VM = vm
VMDIR = vm/
VM_FILES = coreio corewar_gui load main msg ops process ops/op_add ops/op_aff ops/op_and ops/op_fork ops/op_ld ops/op_ldi ops/op_lfork ops/op_live ops/op_lld ops/op_lldi ops/op_nop ops/op_or ops/op_st ops/op_sti ops/op_sub ops/op_xor ops/op_zjmp
VMSRCDIR = $(addprefix $(SRC_DIR), $(VMDIR))
VMOBJDIR = $(addprefix $(OBJ_DIR), $(VMDIR))
VM_OBJECTS=$(addprefix $(VMOBJDIR), $(addsuffix .o, $(VM_FILES)))

ASM = asm
ASMDIR = asm/
ASM_FILES = char_array count error file_op header_utils hexdump instruction_utils instructions is_operand label_utils main operand_error output queue_add resolve_labels string trim util validate_header whitespace zaz_op
ASMSRCDIR = $(addprefix $(SRC_DIR), $(ASMDIR))
ASMOBJDIR = $(addprefix $(OBJ_DIR), $(ASMDIR))
ASM_OBJECTS = $(addprefix $(ASMOBJDIR), $(addsuffix .o, $(ASM_FILES)))

DISASM = disasm
DISASMDIR = disasm/
DISASM_FILES = file_op instruction main print stdin util zaz_op
DISASMSRCDIR = $(addprefix $(SRC_DIR), $(DISASMDIR))
DISASMOBJDIR = $(addprefix $(OBJ_DIR), $(DISASMDIR))
DISASM_OBJECTS = $(addprefix $(DISASMOBJDIR), $(addsuffix .o, $(DISASM_FILES)))

UNAME	:= $(shell uname -s)

ifeq ($(UNAME),Linux)
	MLXDIR = libmlx/linux/
	MLXINC = -I $(MLXDIR) -I inc/linux
	MLXLIB = -L $(MLXDIR) -lmlx -lXext -lX11 -lm
endif

ifeq ($(UNAME),Darwin)
	MLXDIR = libmlx/macos/
	MLXINC = -I $(MLXDIR) -I inc/macos
	MLXLIB = -L $(MLXDIR) -lmlx -framework OpenGL -framework AppKit
endif

LIBMLX = $(addprefix $(MLXDIR), libmlx.a)

BINARIES = $(VM) $(ASM) $(DISASM) $(LIBMLX) $(LIBFT)

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
corewar: $(VM) $(ASM) $(DISASM)
#------------------------------------------------------------------------------
$(VM): $(VM_OBJECTS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(INC) $(LIB) $(MLXLIB) $^ -o $@

$(VM_OBJECTS): $(VMOBJDIR)%.o : $(VMSRCDIR)%.c | $(VMOBJDIR)
	$(CC) $(CFLAGS) $(INC) $(MLXINC) -c $< -o $@

$(VMOBJDIR): $(OBJ_DIR)
	mkdir -p $@
	mkdir -p $@/ops
#------------------------------------------------------------------------------
$(ASM): $(ASM_OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(INC) $(LIB) $^ -o $@

$(ASM_OBJECTS): $(ASMOBJDIR)%.o : $(ASMSRCDIR)%.c | $(ASMOBJDIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(ASMOBJDIR): $(OBJ_DIR)
	mkdir -p $@
#------------------------------------------------------------------------------
$(DISASM): $(DISASM_OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(INC) $(LIB) $^ -o $@

$(DISASM_OBJECTS): $(DISASMOBJDIR)%.o : $(DISASMSRCDIR)%.c | $(DISASMOBJDIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(DISASMOBJDIR): $(OBJ_DIR)
	mkdir -p $@
#------------------------------------------------------------------------------
$(LIBFT):
	make -C libft/

$(LIBMLX):
	make -C $(MLXDIR)

$(OBJ_DIR):
	mkdir -p $@
#------------------------------------------------------------------------------

again:
	rm -f $(VM_OBJECTS)
	make vm

clean:
	make $@ -C $(MLXDIR)
	@make $@ -C libft/
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed$(NC)"

rmcor:
	find . -iname "*.cor" -exec rm {} \;

fclean: clean
	@make $@ -C libft/
	@rm -f $(BINARIES)
	@echo "$(RED)$(BINARIES) removed$(NC)"

re: fclean all
