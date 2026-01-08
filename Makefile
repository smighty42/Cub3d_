NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = \
	src/main.c \
	src/parser/parser.c \
	src/parser/map_validation.c \
	src/background.c \
	src/player.c \
	src/ray_casting.c \
	src/controller.c \
	src/draw_wall.c \
	src/parser/utils.c \
	src/parser/string_utils.c \
	src/parser/texture_loader.c \
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
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(SRCS) $(SRCS_GNL) $(MLX_FLAGS) $(INCLUDES) -lm -o $(NAME) -L/usr/X11/lib

clean:
	make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
