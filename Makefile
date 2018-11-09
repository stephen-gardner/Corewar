#!/usr/bin/make -f

################################################################################
# SETTINGS                                                                     #
################################################################################

NAME = corewar
CC = gcc
CFLAGS += -Wall -Werror -Wextra
CFLAGS += -Ofast -funroll-loops -Wno-unused-result
#CFLAGS += -g #-fsanitize=address
#CFLAGS += -Wunused-macros -Wunused-local-typedefs
INC = -I inc -I lib/libft/inc
LIBFTDIR = lib/libft/
LIBFT = $(LIBFTDIR)libft.a
MLXDIR = lib/libmlx/
SRC_DIR = src/
OBJ_DIR = obj/

VM = corewar
VMDIR = vm/
VM_FILES = champ coreio main msg ops process
VM_FILES += ops/op_add ops/op_aff ops/op_and ops/op_fork ops/op_ld ops/op_ldi ops/op_lfork ops/op_live ops/op_lld ops/op_lldi ops/op_nop ops/op_or ops/op_st ops/op_sti ops/op_sub ops/op_xor ops/op_zjmp
VMSRCDIR = $(addprefix $(SRC_DIR), $(VMDIR))
VMOBJDIR = $(addprefix $(OBJ_DIR), $(VMDIR))
VM_OBJECTS=$(addprefix $(VMOBJDIR), $(addsuffix .o, $(VM_FILES)))

GUI_FILES = gui_main gui_bars gui_blocks gui_colors gui_cpf gui_hooks gui_pc_boxes gui_text gui_loop
UNAME	:= $(shell uname -s)
ifeq ($(UNAME),Darwin)
	GUI_FILES += gui_mlx_macos
endif
ifeq ($(UNAME),Linux)
	GUI_FILES += gui_mlx_linux
endif
GUIDIR = gui/
GUISRCDIR = $(addprefix $(SRC_DIR), $(GUIDIR))
GUIOBJDIR = $(addprefix $(OBJ_DIR), $(GUIDIR))
GUI_OBJECTS= $(addprefix $(GUIOBJDIR), $(addsuffix .o, $(GUI_FILES)))

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

ifeq ($(UNAME),Linux)
	MLXDIR := $(MLXDIR)linux/
	MLXINC = -I $(MLXDIR) -I inc/linux/
	MLXLIB = -L $(MLXDIR) -lX11 -lXext -lmlx -lbsd -lm
endif

ifeq ($(UNAME),Darwin)
	MLXDIR := $(MLXDIR)macos/
	MLXINC = -I $(MLXDIR) -I inc/macos/
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

all: $(VM) $(ASM) $(DISASM)
#------------------------------------------------------------------------------
$(VM): $(VM_OBJECTS) $(GUI_OBJECTS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $^ $(LIB) $(MLXLIB) -o $@

$(VM_OBJECTS): $(VMOBJDIR)%.o : $(VMSRCDIR)%.c | $(VMOBJDIR)
	$(CC) $(CFLAGS) $(INC) $(MLXINC) -c $< -o $@

$(VMOBJDIR): $(OBJ_DIR)
	mkdir -p $@
	mkdir -p $@/ops
	mkdir -p $@/gui
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
$(GUI_OBJECTS): $(GUIOBJDIR)%.o : $(GUISRCDIR)%.c | $(GUIOBJDIR)
	$(CC) $(CFLAGS) $(INC) $(MLXINC) -c $< -o $@

$(GUIOBJDIR): $(OBJ_DIR)
	mkdir -p $@

#------------------------------------------------------------------------------
$(LIBFT):
	make -C $(LIBFTDIR)

$(LIBMLX):
	make -C $(MLXDIR)

$(OBJ_DIR):
	mkdir -p $@
#------------------------------------------------------------------------------

again:
	rm -f $(VM_OBJECTS) $(GUI_OBJECTS)
	make $(VM)

clean:
	make $@ -C $(MLXDIR)
	@make $@ -C $(LIBFTDIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed$(NC)"

testasm: $(ASM)
	bash -c 'for f in tests/champions/*.s; do ./asm $$f; done'
asmtest: testasm

testgui: $(VM)
	bash -c './corewar -q -g tests/champions/Gagnant.cor tests/champions/Douceur_power.cor tests/champions/overwatch.cor tests/champions/Asombra.cor'
guitest: testgui

rmcor:
	find . -iname "*.cor" -exec rm {} \;

norminette:
	norminette lib/libft/ inc/ src/

norm: norminette

fclean: clean
	@make $@ -C $(LIBFTDIR)
	@rm -f $(BINARIES)
	@echo "$(RED)$(BINARIES) removed$(NC)"

re: fclean all
