#!/usr/bin/make -f

################################################################################
# SETTINGS                                                                     #
################################################################################

NAME = libft.a
AR = ar
ARFLAGS = -rcs
AS = nasm
ASFLAGS += -f macho64
CC = gcc
CFLAGS += -Wall -Werror -Wextra
CFLAGS += -Ofast
CFLAGS += #-g -fsanitize=address
INC = -I inc
SRC_DIR = src
OBJ_DIR = obj

ifeq ($(shell uname -s),Linux)
	CFLAGS += -Wno-unused-result
endif

# [ BASE ]

SRC = \
	ft_atoi\
	ft_memalloc\
	ft_memcpy\
	ft_memdel\
	ft_memset\
	ft_revbytes\
	ft_stpcpy\
	ft_stpncpy\
	ft_strchr\
	ft_strcmp\
	ft_strcpy\
	ft_strdup\
	ft_strlen\
	ft_strncmp\
	ft_strncpy\
	ft_strnlen\
	ft_strsplit\
	ft_strsub\
	ft_strupcase

# [ PRINTF ]

SRC += \
	printf/conv_char\
	printf/conv_float\
	printf/conv_int\
	printf/conv_int_deprecated\
	printf/conv_misc\
	printf/conv_wchar\
	printf/ft_printf\
	printf/ft_vprintf\
	printf/parser\
	printf/process\
	printf/util\
	printf/util_int

# [ MEMORY MANAGER ]

SRC += \
	memmgr/ft_mchain\
	memmgr/ft_mladd\
	memmgr/ft_mlalloc\
	memmgr/ft_mlpop\
	memmgr/ft_mlrev

# [ OTHER ]

SRC += \
	getopt/ft_getopt\
	get_next_line/get_next_line

OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC))

################################################################################
# COLORS                                                                       #
################################################################################

NC = \033[0m
GREEN = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m

################################################################################
# RULES                                                                        #
################################################################################

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(ARFLAGS) $@ $(OBJ)
	@echo "$(GREEN)DONE$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	@$(AS) $(ASFLAGS) $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed$(NC)"

re: fclean all
