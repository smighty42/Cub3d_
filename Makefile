NAME = cub3D

MAKEFLAGS 			+= --no-print-directory

CC = cc
CFLAGS = -Wall -Wextra -Werror


GREEN = \033[0;32m
CYAN = \033[0;36m
RESET = \033[0m

SRCS = \
	src/main.c \
	src/parser/parser.c \
	src/background.c \
	src/player.c \
	src/ray_casting.c \
	src/controller.c \
	src/draw_wall.c 

SRCS_PARSER= \
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

SRCS_GNL=\
	get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c


OBJS = $(SRCS:.c=.o)

MLX_DIR = mlx
MLX_FLAGS = -L$(MLX_DIR)  -lmlx -lXext -lX11 -lz
INCLUDES = -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(SRCS)
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
	@echo "$(GREEN)Compiling MLX library...$(RESET)"
	@make -C $(MLX_DIR)
	@echo "$(GREEN)Compiling cub3D...$(RESET)"
	@$(CC) $(CFLAGS) $(SRCS) $(SRCS_GNL) $(SRCS_PARSER) $(MLX_FLAGS) $(INCLUDES) -lm -o $(NAME) -L/usr/X11/lib
	@echo "$(GREEN)✓ cub3D compiled successfully!$(RESET)"

clean:
	@echo "$(CYAN)Cleaning object files...$(RESET)"
	-@make -C $(MLX_DIR) clean
	@rm -f $(OBJS)
	@echo "$(GREEN)✓ Clean complete!$(RESET)"

fclean: clean
	@echo "$(CYAN)Removing executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Full clean complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
