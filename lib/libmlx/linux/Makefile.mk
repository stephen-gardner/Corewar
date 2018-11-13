## Please use configure script

################################################################################
# SETTINGS                                                                     #
################################################################################

NAME = libmlx.a
AR = ar
ARFLAGS = -rcs
CC = gcc
CFLAGS += -Wno-implicit-function-declaration -Wno-unused-result -Wno-return-type -Wno-parentheses
CFLAGS += -Ofast -funroll-loops
CFLAGS += #-g -fsanitize=address
INC = %%%%
SRC_DIR = src
SRC	= \
	mlx_clear_window\
	mlx_destroy_image\
	mlx_destroy_window\
	mlx_expose_hook\
	mlx_flush_event\
	mlx_get_color_value\
	mlx_get_data_addr\
	mlx_hook\
	mlx_init\
	mlx_int_anti_resize_win\
	mlx_int_do_nothing\
	mlx_int_get_visual\
	mlx_int_param_event\
	mlx_int_set_win_event_mask\
	mlx_int_str_to_wordtab\
	mlx_int_wait_first_expose\
	mlx_key_hook\
	mlx_loop\
	mlx_loop_hook\
	mlx_mouse_hook\
	mlx_new_image\
	mlx_new_window\
	mlx_pixel_put\
	mlx_put_image_to_window\
	mlx_rgb\
	mlx_string_put\
	mlx_xpm
OBJ_DIR = obj
OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC))

################################################################################
# COLORS                                                                       #
################################################################################

NC = \033[0m
GREEN = \033[1;32m
RED = \033[1;31m

################################################################################
# RULES                                                                        #
################################################################################

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(ARFLAGS) $@ $(OBJ)
	@echo "$(GREEN)DONE$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC) -I inc -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed$(NC)"

re: fclean all
