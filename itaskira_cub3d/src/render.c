#include "../include/cub3d.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x
				* (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static int	get_texture_color(t_img *texture, int tex_x, int tex_y)
{
	char	*dst;

	if (tex_x >= 0 && tex_x < texture->width
		&& tex_y >= 0 && tex_y < texture->height)
	{
		dst = texture->addr + (tex_y * texture->line_length
				+ tex_x * (texture->bits_per_pixel / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}

static t_img	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (game->textures->east);
		else
			return (game->textures->west);
	}
	else
	{
		if (ray->dir_y > 0)
			return (game->textures->south);
		else
			return (game->textures->north);
	}
}

static void	calculate_texture_x(t_game *game, t_ray *ray,
				t_img *texture, int *tex_x)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player->y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player->x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * (double)texture->width);
	if (ray->side == 0 && ray->dir_x > 0)
		*tex_x = texture->width - *tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		*tex_x = texture->width - *tex_x - 1;
	if (*tex_x < 0)
		*tex_x = 0;
	if (*tex_x >= texture->width)
		*tex_x = texture->width - 1;
}

static void	draw_wall_stripe(t_game *game, int x, t_ray *ray,
				t_img *texture)
{
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	calculate_texture_x(game, ray, texture, &tex_x);
	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		tex_pos += step;
		color = get_texture_color(texture, tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(game->img, x, y, color);
		y++;
	}
}

void	draw_vertical_line(t_game *game, int x, t_ray *ray)
{
	t_img	*texture;
	int		y;

	texture = get_wall_texture(game, ray);
	if (!texture)
		return ;
	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(game->img, x, y, game->textures->ceiling_color);
		y++;
	}
	draw_wall_stripe(game, x, ray, texture);
	y = ray->draw_end + 1;
	while (y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(game->img, x, y, game->textures->floor_color);
		y++;
	}
}

void	draw_ceiling_floor(t_game *game, int x, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(game->img, x, y, game->textures->ceiling_color);
		y++;
	}
	y = ray->draw_end;
	while (y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(game->img, x, y, game->textures->floor_color);
		y++;
	}
}

int	render_frame(t_game *game)
{
	memset(game->img->addr, 0, WINDOW_HEIGHT * game->img->line_length);
	perform_raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (0);
}
