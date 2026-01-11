/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:10:16 by smayti            #+#    #+#             */
/*   Updated: 2026/01/11 15:22:39 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdlib.h>

void	clean(t_game *game)
{
	cleanup_textures(game);
	if (game->image.new_image)
		mlx_destroy_image(game->mlx, game->image.new_image);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

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

int	close_window(t_game *game)
{
	cleanup_textures(game);
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
	gc_free_all(&game->gc);
	exit(0);
	return (0);
}
