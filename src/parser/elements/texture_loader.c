/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:11:47 by smayti            #+#    #+#             */
/*   Updated: 2026/01/11 15:42:54 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"
#include "../../../mlx/mlx.h"

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
		clean(game);
		cleanup_textures(game);
		free_exit(game, "Texture could not be loaded");
	}
}
