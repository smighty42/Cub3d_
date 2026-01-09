/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira < itaskira@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:11:47 by smayti            #+#    #+#             */
/*   Updated: 2026/01/09 16:28:32 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
			
	if (!game->texture.north_img
		|| !game->texture.south_img
		|| !game->texture.east_img
		|| !game->texture.west_img)
	{
		cleanup_textures(game);
		free_exit(game, "Texture could not be loaded");
	}
}
