#include "../include/cub3d.h"

void	cleanup_textures(t_game *game)
{
	if (game->textures)
	{
		if (game->textures->north)
		{
			if (game->textures->north->img && game->mlx)
				mlx_destroy_image(game->mlx, game->textures->north->img);
			free(game->textures->north);
		}
		if (game->textures->south)
		{
			if (game->textures->south->img && game->mlx)
				mlx_destroy_image(game->mlx, game->textures->south->img);
			free(game->textures->south);
		}
		if (game->textures->east)
		{
			if (game->textures->east->img && game->mlx)
				mlx_destroy_image(game->mlx, game->textures->east->img);
			free(game->textures->east);
		}
		if (game->textures->west)
		{
			if (game->textures->west->img && game->mlx)
				mlx_destroy_image(game->mlx, game->textures->west->img);
			free(game->textures->west);
		}
		free(game->textures);
		game->textures = NULL;
	}
}

void	cleanup_map(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	// Clean up texture paths
	if (game->north_path)
	{
		free(game->north_path);
		game->north_path = NULL;
	}
	if (game->south_path)
	{
		free(game->south_path);
		game->south_path = NULL;
	}
	if (game->east_path)
	{
		free(game->east_path);
		game->east_path = NULL;
	}
	if (game->west_path)
	{
		free(game->west_path);
		game->west_path = NULL;
	}

	// Clean up textures
	cleanup_textures(game);

	// Clean up map
	cleanup_map(game);

	// Clean up player
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}

	// Clean up image
	if (game->img)
	{
		if (game->img->img && game->mlx)
			mlx_destroy_image(game->mlx, game->img->img);
		free(game->img);
		game->img = NULL;
	}

	// Clean up window
	if (game->win && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}

	// Clean up MLX
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}