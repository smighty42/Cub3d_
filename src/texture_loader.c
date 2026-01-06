#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	load_textures(t_game *game)
{
	int	width;
	int	height;

	game->texture.north_img = mlx_xpm_file_to_image(game->mlx,
			game->texture.north, &width, &height);
	game->texture.south_img = mlx_xpm_file_to_image(game->mlx,
			game->texture.south, &width, &height);
	game->texture.east_img = mlx_xpm_file_to_image(game->mlx,
			game->texture.east, &width, &height);
	game->texture.west_img = mlx_xpm_file_to_image(game->mlx,
			game->texture.west, &width, &height);
	if (!game->texture.north_img)
		printf("Warning: Could not load north texture: %s\n",
			game->texture.north);
	if (!game->texture.south_img)
		printf("Warning: Could not load south texture: %s\n",
			game->texture.south);
	if (!game->texture.east_img)
		printf("Warning: Could not load east texture: %s\n",
			game->texture.east);
	if (!game->texture.west_img)
		printf("Warning: Could not load west texture: %s\n",
			game->texture.west);
}
