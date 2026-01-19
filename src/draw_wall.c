/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:11:05 by smayti            #+#    #+#             */
/*   Updated: 2026/01/19 14:17:39 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>

void	*get_texture_img(t_game *game, t_raycast ray)
{
	if (ray.hit_side == 0)
	{
		if (cos(ray.ray_angle) > 0)
			return (game->texture.east_img);
		else
			return (game->texture.west_img);
	}
	else
	{
		if (sin(ray.ray_angle) > 0)
			return (game->texture.south_img);
		else
			return (game->texture.north_img);
	}
}

int	get_texture_color(t_game *game, t_raycast ray, int y, int wall_height)
{
	t_texture_calc	t;
	void			*texture_img;

	texture_img = get_texture_img(game, ray);
	t.data = mlx_get_data_addr(texture_img,
			&t.bpp, &t.line_len, &t.endian);
	if (!t.data)
	{
		clean(game);
		free_exit(game, "MLX initialization failed.");
	}
	t.x = (int)(ray.wall_x * TEX_SIZE);
	if ((ray.hit_side == 0 && cos(ray.ray_angle) > 0)
		|| (ray.hit_side == 1 && sin(ray.ray_angle) < 0))
		t.x = TEX_SIZE - t.x - 1;
	t.draw_start = (WIN_HEIGHT - wall_height) / 2;
	t.y = (int)((y - t.draw_start) * TEX_SIZE / wall_height);
	return (*(int *)(t.data
		+ (t.y * t.line_len + t.x * (t.bpp / 8))));
}

void	draw_wall_slice(t_game *game, int x, t_raycast ray)
{
	int	wall_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	color;

	ray.distance = ray.distance * cos(ray.ray_angle - game->player.dir);
	wall_height = (int)(WIN_HEIGHT / ray.distance);
	draw_start = (WIN_HEIGHT - wall_height) / 2;
	draw_end = (WIN_HEIGHT + wall_height) / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	y = draw_start;
	while (y <= draw_end)
	{
		color = get_texture_color(game, ray, y, wall_height);
		my_put_pixel(game, x, y, color);
		y++;
	}
}
