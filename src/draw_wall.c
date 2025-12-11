#include "../minilibx/mlx.h"
#include "../cub3d.h"
#include <math.h>
#include <stdio.h>
int get_texture_color(t_game *game, t_raycast ray, int y, int wall_height)
{
    void *texture_img;
    char *texture_data;
    int tex_x, tex_y;
    int color;
    int bits_per_pixel, line_length, endian;
    int draw_start;

    
    if (ray.hit_side == 0) 
    {
        if (cos(ray.ray_angle) > 0)
            texture_img = game->texture.east_img;
        else
            texture_img = game->texture.west_img;
    }
    else 
    {
        if (sin(ray.ray_angle) > 0)
            texture_img = game->texture.south_img;
        else
            texture_img = game->texture.north_img;
    }



    texture_data = mlx_get_data_addr(texture_img, &bits_per_pixel, &line_length, &endian);

    
    tex_x = (int)(ray.wall_x * TEX_SIZE);
    if ((ray.hit_side == 0 && cos(ray.ray_angle) > 0) || 
        (ray.hit_side == 1 && sin(ray.ray_angle) < 0))
        tex_x = TEX_SIZE - tex_x - 1;

    draw_start = (WIN_HEIGHT - wall_height) / 2;
    tex_y = (int)((y - draw_start) * TEX_SIZE / wall_height);

    
    color = *(int*)(texture_data + (tex_y * line_length + tex_x * (bits_per_pixel / 8)));

    return color;
}
