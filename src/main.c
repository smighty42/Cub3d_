/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira < itaskira@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:11:02 by smayti            #+#    #+#             */
/*   Updated: 2026/01/11 12:54:56 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <unistd.h>
#include <stdlib.h>

void	init(t_game *game)
{
	game->width = WIN_WIDTH;
	game->height = WIN_HEIGHT;
	game->mlx = mlx_init();
	if (!game->mlx)
		free_exit(game, "MLX initialization failed.");
	game->win = mlx_new_window(game->mlx, game->width, game->height, "cub3d");
	if (!game->win)
		free_exit(game, "Window creation failed.");
}

void	put_celling_floor(t_game *game)
{
	game->image.new_image = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->image.new_image)
		free_exit(game, "Image creation failed.");
	game->image.add = mlx_get_data_addr(game->image.new_image,
			&game->image.pixel_bit, &game->image.line_length_byte,
			&game->image.endian);
	if (!game->image.add)
		free_exit(game, "Image address failed.");
}

void	ft_resetter(t_game *game)
{
	game->keys.w = 0;
	game->keys.s = 0;
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->map.map = NULL;
	game->texture.north = NULL;
	game->texture.south = NULL;
	game->texture.east = NULL;
	game->texture.west = NULL;
	game->floor_color.r = -1;
	game->floor_color.g = -1;
	game->floor_color.b = -1;
	game->floor_color.rgb = -1;
	game->ceiling_color.r = -1;
	game->ceiling_color.g = -1;
	game->ceiling_color.b = -1;
	game->ceiling_color.rgb = -1;
	game->gc = NULL;
}

void	init_game(t_game *game, char *file)
{
	ft_resetter(game);
	parse_cub_file(game, file);
	if (!game->map.map || !game->texture.north || !game->texture.south
		|| !game->texture.east || !game->texture.west)
		free_exit(game, "Parsing failed");
	validate_map(game);
	init(game);
	put_celling_floor(game);
	load_textures(game);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		write(2, "Usage: ./cub3D <map.cub>\n", 26);
		return (1);
	}
	init_game(&game, av[1]);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	mlx_loop_hook(game.mlx, main_loop, &game);
	mlx_loop(game.mlx);
	gc_free_all(&game.gc);
	return (0);
}
