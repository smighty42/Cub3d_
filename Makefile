NAME = cub3D

MAKEFLAGS += --no-print-directory

CC = cc
CFLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
CYAN = \033[0;36m
RESET = \033[0m

OBJ_DIR = obj
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a

SRCS_MAIN = \
	src/main.c \
	src/parser/parser.c \
	src/background.c \
	src/player.c \
	src/ray_casting.c \
	src/controller.c \
	src/draw_wall.c

SRCS_PARSER = \
	src/parser/utils/utils.c \
	src/parser/utils/string_utils.c \
	src/parser/elements/texture_loader.c \
	src/parser/utils/parser_utils.c \
	src/parser/elements/parser_texture.c \
	src/parser/elements/parser_color.c \
	src/parser/elements/parser_map.c \
	src/parser/elements/parser_checks.c \
	src/parser/validation/map_validation.c \
	src/parser/validation/map_checks.c \
	src/parser/validation/map_walls.c \
	src/parser/validation/map_neighbors.c \
	src/parser/validation/map_enclosure.c \
	src/parser/validation/map_player.c \
	src/parser/utils/ft_split_gc.c \
	src/parser/utils/utils2.c \
	src/update_player_position.c \
	src/cleanup.c \
	src/gc.c

SRCS_GNL = \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c

ALL_SRCS = $(SRCS_MAIN) $(SRCS_PARSER) $(SRCS_GNL)
OBJS = $(ALL_SRCS:%.c=$(OBJ_DIR)/%.o)

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lz -lm
INCLUDES = -I$(MLX_DIR) -Isrc -Isrc/parser

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	@echo "$(CYAN)"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⣶⡄⠱⣦⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠛⠉⡙⣿⣿⡄⢹⣧⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⡿⢋⣠⠾⠋⠉⢹⣿⣷⢸⣿⡆⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⠏⣠⠞⠁⠀⠀⠀⢸⣿⣿⢸⣿⡇⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⠟⢡⡾⠋⠀⠀⠀⠀⠀⢸⣿⡇⢸⣿⠃⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⡿⠁⣴⡟⠁⠀⠀⠀⠀⠀⠀⣿⡿⠀⣾⡟⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⠏⢠⣾⠏⠀⠀⠀⠀⠀⠀⠀⣼⠟⢁⣼⣿⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⣴⣄⠁⠰⡿⠃⠀⠀⠀⠀⠀⠀⢠⡾⠁⣴⣿⣿⡟⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⠆⠀⠀⠀⠀⠀⠀⠀⢀⡿⢀⣾⣿⣿⣿⡇⠀⠀⠀"
	@echo "⠀⠀⠀⠀⢀⣴⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⡼⠁⣼⡿⢃⣿⣿⠇⠀⠀⠀"
	@echo "⠀⠀⠀⢠⣾⣿⣿⣿⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⣼⠟⠁⣸⣿⠏⠀⠀⠀⠀"
	@echo "⠀⠀⣰⣿⣿⣿⣿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⠃⠀⠀⠀⠀⠀"
	@echo "⠀⣾⣿⣿⣿⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠛⠛⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "$(RESET)"
	@echo "$(GREEN)Linking cub3D...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) -L/usr/X11/lib
	@echo "$(GREEN)✓ cub3D successfully built!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX_LIB):
	@echo "$(GREEN)Compiling MLX library...$(RESET)"
	@make -C $(MLX_DIR)

clean:
	@echo "$(CYAN)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean
	@echo "$(GREEN)✓ Clean complete!$(RESET)"

fclean: clean
	@echo "$(CYAN)Removing executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Full clean complete!$(RESET)"

re: fclean all

norm:
	norminette src get_next_line cub3d.h

.PHONY: all clean fclean re norm