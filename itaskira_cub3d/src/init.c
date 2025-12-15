#include "../include/cub3d.h"

int	init_game(t_game *game)
{
	if (init_mlx(game) != 0)
		return (-1);
	if (init_player(game) != 0)
		return (-1);
	if (init_textures(game) != 0)
		return (-1);
	return (0);
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_exit("Failed to initialize MLX"), -1);
	
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return (error_exit("Failed to create window"), -1);
	
	game->img = malloc(sizeof(t_img));
	if (!game->img)
		return (error_exit("Failed to allocate image structure"), -1);
	
	game->img->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img->img)
		return (error_exit("Failed to create image"), -1);
	
	game->img->addr = mlx_get_data_addr(game->img->img,
		&game->img->bits_per_pixel, &game->img->line_length,
		&game->img->endian);
	if (!game->img->addr)
		return (error_exit("Failed to get image data address"), -1);
	
	return (0);
}

int	init_player(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (error_exit("Failed to allocate player structure"), -1);
	
	// Find player position will be set in map parsing
	if (find_player(game) != 0)
		return (error_exit("Player not found in map"), -1);
	
	return (0);
}

t_img	*load_texture(t_game *game, char *path)
{
	t_img	*texture;

	texture = malloc(sizeof(t_img));
	if (!texture)
		return (NULL);
	
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
		&texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Error: Failed to load texture: %s\n", path);
		free(texture);
		return (NULL);
	}
	
	texture->addr = mlx_get_data_addr(texture->img,
		&texture->bits_per_pixel, &texture->line_length,
		&texture->endian);
	if (!texture->addr)
	{
		mlx_destroy_image(game->mlx, texture->img);
		free(texture);
		return (NULL);
	}
	
	return (texture);
}

int	init_textures(t_game *game)
{
	game->textures = malloc(sizeof(t_texture));
	if (!game->textures)
		return (error_exit("Failed to allocate texture structure"), -1);
	
	game->textures->north = load_texture(game, game->north_path);
	if (!game->textures->north)
		return (error_exit("Failed to load north texture"), -1);
	
	game->textures->south = load_texture(game, game->south_path);
	if (!game->textures->south)
		return (error_exit("Failed to load south texture"), -1);
	
	game->textures->east = load_texture(game, game->east_path);
	if (!game->textures->east)
		return (error_exit("Failed to load east texture"), -1);
	
	game->textures->west = load_texture(game, game->west_path);
	if (!game->textures->west)
		return (error_exit("Failed to load west texture"), -1);
	
	return (0);
}