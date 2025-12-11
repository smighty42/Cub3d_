#include "../cub3d.h"
#include "../minilibx/mlx.h"
#include <math.h>
#include <stdio.h>

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



	//gerek yok buna ama şimdilik kalsın aynalama işlemi 
	/*if ((dda->side == 0 && ray->ray_angle > PI / 2 && ray->ray_angle < 3 * PI
			/ 2) || (dda->side == 1 && (ray->ray_angle < PI
				|| ray->ray_angle > 2 * PI)))
	{
		// Texture koordinatını ters çevir
		ray->wall_x = 1.0 - ray->wall_x;
	}*/
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

void	perform_raycasting(t_game *game)
{
	int			x;
	double		ray_angle;
	double		angle_step;
	t_raycast	ray;

	angle_step = (PI / 3) / WIN_WIDTH;       // 60 derece görüş açısı
	ray_angle = game->player.dir - (PI / 6); // -30 derece başlangıç
	for (x = 0; x < WIN_WIDTH; x++)
	{
		ray = cast_ray(game, ray_angle);
		draw_wall_slice(game, x, ray);
		ray_angle += angle_step;
	}
}
