NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = \
	src/main1.c \
	src/parser.c \
	src/map_validation.c \
	src/background.c \
	src/player.c \
	src/ray_casting.c \
	src/controller.c \
	src/draw_wall.c \
	src/utils.c \
	src/string_utils.c \
	src/get_next_line.c \
	src/texture_loader.c \
	src/update_player_position.c \
	src/cleanup.c


OBJS = $(SRCS:.c=.o)

MLX_DIR = mlx
MLX_FLAGS = -L$(MLX_DIR)  -lmlx -lXext -lX11 -lz
INCLUDES = -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(SRCS)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(SRCS) $(MLX_FLAGS) $(INCLUDES) -lm -o $(NAME) -L/usr/X11/lib

clean:
	make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
