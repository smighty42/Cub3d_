/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:10:42 by smayti            #+#    #+#             */
/*   Updated: 2026/01/11 15:23:34 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

void	ray_step(t_raycast *ray, double angle)
{
	if (cos(angle) < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->ray_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->ray_x) * ray->delta_dist_x;
	}
	if (sin(angle) < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->ray_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->ray_y) * ray->delta_dist_y;
	}
}

void	dda_calculator(t_game *game, t_dda *dda, t_raycast *ray)
{
	while (dda->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			dda->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			dda->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_x >= game->map.width
			|| ray->map_y >= game->map.height
			|| game->map.map[ray->map_y][ray->map_x] == '1')
			dda->hit = 1;
	}
}

void	texture_and_calculator(t_raycast *ray, t_dda *dda)
{
	if (dda->side == 0)
		ray->distance = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->distance = ray->side_dist_y - ray->delta_dist_y;
	ray->hit_side = dda->side;
	if (dda->side == 0)
		ray->wall_x = ray->ray_y + ray->distance * sin(ray->ray_angle);
	else
		ray->wall_x = ray->ray_x + ray->distance * cos(ray->ray_angle);
	ray->wall_x = fmod(ray->wall_x, 1.0);
}

t_raycast	cast_ray(t_game *game, double angle)
{
	t_raycast	ray;
	t_dda		dda;

	dda.hit = 0;
	ray.ray_x = game->player.x;
	ray.ray_y = game->player.y;
	ray.ray_angle = angle;
	ray.map_x = (int)ray.ray_x;
	ray.map_y = (int)ray.ray_y;
	ray.delta_dist_x = fabs(1 / cos(angle));
	ray.delta_dist_y = fabs(1 / sin(angle));
	ray_step(&ray, angle);
	dda_calculator(game, &dda, &ray);
	texture_and_calculator(&ray, &dda);
	return (ray);
}

void	perform_raycasting(t_game *game)
{
	int			x;
	double		ray_angle;
	double		angle_step;
	t_raycast	ray;

	x = 0;
	angle_step = ((PI / 3) / WIN_WIDTH);
	ray_angle = game->player.dir - (PI / 6);
	while (x < WIN_WIDTH)
	{
		ray = cast_ray(game, ray_angle);
		draw_wall_slice(game, x, ray);
		ray_angle += angle_step;
		x++;
	}
}
