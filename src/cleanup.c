#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdlib.h>

void	cleanup_textures(t_game *game)
{
	if (game->texture.north_img)
	{
		mlx_destroy_image(game->mlx, game->texture.north_img);
		game->texture.north_img = NULL;
	}
	if (game->texture.south_img)
	{
		mlx_destroy_image(game->mlx, game->texture.south_img);
		game->texture.south_img = NULL;
	}
	if (game->texture.east_img)
	{
		mlx_destroy_image(game->mlx, game->texture.east_img);
		game->texture.east_img = NULL;
	}
	if (game->texture.west_img)
	{
		mlx_destroy_image(game->mlx, game->texture.west_img);
		game->texture.west_img = NULL;
	}
}

void	cleanup_map(t_game *game)
{
	int	i;

	if (game->map.map)
	{
		i = 0;
		while (game->map.map[i])
		{
			free(game->map.map[i]);
			i++;
		}
		free(game->map.map);
		game->map.map = NULL;
	}
}

int	close_window(t_game *game)
{
	cleanup_textures(game);

	cleanup_map(game);

	if (game->image.new_image)
	{
		mlx_destroy_image(game->mlx, game->image.new_image);
		game->image.new_image = NULL;
	}

	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}

	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}

	exit(0);
	return (0);
}