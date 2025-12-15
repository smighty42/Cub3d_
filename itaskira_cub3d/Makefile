NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I include -I $(MLX_DIR)

# MLX library for macOS with X11
MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
X11_FLAGS = -L/usr/X11/lib

# Source files
SRC_DIR = src
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/init.c \
       $(SRC_DIR)/parsing.c \
       $(SRC_DIR)/map_validation.c \
       $(SRC_DIR)/raycasting.c \
       $(SRC_DIR)/render.c \
       $(SRC_DIR)/controls.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/cleanup.c

OBJS = $(SRCS:.c=.o)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(X11_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re