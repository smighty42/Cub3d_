#include "../mlx/mlx.h"
#include "../cub3d.h"
#include <stdio.h>


void my_put_pixel(t_game *game,int x,int y,int color)
{
    char *dst;
    dst = game->image.add+(y*(game->image.line_length_byte) + x*(game->image.pixel_bit/8));
    *(unsigned int *)dst=color;
}

void mlx_put_color2(t_game *game, int x,int y)
{
     int color_floor=( game->floor_color.r <<16)|(game->floor_color.g<<8)|(game->floor_color.b);
        while(y < game->height)
    {
        x=0;
        while(x<game->width)
        {
        my_put_pixel(game,x,y,color_floor);
        x++;
        }
        y++;
    }
}

void mlx_put_color(t_game *game)
{
   
    int ceiling_color=(game->ceiling_color.r<<16)|(game->ceiling_color.g<<8)|(game->ceiling_color.b);
    int x;
    int y=0;

    while(y < game->height/2)
    {
        x=0;
        while(x<game->width)
        {
            my_put_pixel(game,x,y,ceiling_color);
            x++;
        }
        y++;
    }
    mlx_put_color2(game,x,y);

}

void render_floor_celling(t_game *game)
{
    mlx_put_color(game);
}