NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = \
	src/main1.c \
	src/fake_parser_map1.c \
	src/background.c \
	src/player.c \
	src/ray_casting.c \
	src/controller.c \
	src/draw_wall.c \


OBJS = $(SRCS:.c=.o)

MLX_DIR = minilibx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext
INCLUDES = -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(SRCS)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(SRCS) $(MLX_FLAGS) $(INCLUDES) -lm -o $(NAME)

clean:
	make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
