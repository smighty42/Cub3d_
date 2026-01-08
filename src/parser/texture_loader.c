/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:11:47 by smayti            #+#    #+#             */
/*   Updated: 2026/01/06 16:51:58 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	exit_error(t_game *game, char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);

	// MLX image cleanup
	if (game->texture.north_img)
		mlx_destroy_image(game->mlx, game->texture.north_img);
	if (game->texture.south_img)
		mlx_destroy_image(game->mlx, game->texture.south_img);
	if (game->texture.east_img)
		mlx_destroy_image(game->mlx, game->texture.east_img);
	if (game->texture.west_img)
		mlx_destroy_image(game->mlx, game->texture.west_img);

	gc_free_all(&game->gc);
	exit(1);
}

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
		exit_error(game, "Error\nTexture could not be loaded");
	}
}
