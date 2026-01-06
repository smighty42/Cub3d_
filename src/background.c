/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:11:14 by smayti            #+#    #+#             */
/*   Updated: 2026/01/06 15:11:15 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../cub3d.h"
#include <stdio.h>

void	my_put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->image.add + (y * (game->image.line_length_byte) + x
			* (game->image.pixel_bit / 8));
	*(unsigned int *)dst = color;
}

void	mlx_put_color2(t_game *game, int x, int y)
{
	int	color_floor;

	color_floor = (game->floor_color.r << 16)
		| (game->floor_color.g << 8)
		| (game->floor_color.b);
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			my_put_pixel(game, x, y, color_floor);
			x++;
		}
		y++;
	}
}

void	mlx_put_color(t_game *game)
{
	int	ceiling_color;
	int	x;
	int	y;

	ceiling_color = (game->ceiling_color.r << 16)
		| (game->ceiling_color.g << 8)
		| (game->ceiling_color.b);
	y = 0;
	while (y < game->height / 2)
	{
		x = 0;
		while (x < game->width)
		{
			my_put_pixel(game, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	mlx_put_color2(game, x, y);
}

void	render_floor_celling(t_game *game)
{
	mlx_put_color(game);
}
