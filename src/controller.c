#include "../mlx/mlx.h"
#include "../cub3d.h"
#include <math.h>
#include <stdlib.h>

int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->keys.w = 1;
    else if (keycode == KEY_S)
        game->keys.s = 1;
    else if (keycode == KEY_A)
        game->keys.a = 1;
    else if (keycode == KEY_D)
        game->keys.d = 1;
    else if (keycode == KEY_LEFT)
        game->keys.left = 1;
    else if (keycode == KEY_RIGHT)
        game->keys.right = 1;
    else if (keycode == KEY_ESC)
        close_window(game);
    
    return 0;
}

int key_release(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->keys.w = 0;
    else if (keycode == KEY_S)
        game->keys.s = 0;
    else if (keycode == KEY_A)
        game->keys.a = 0;
    else if (keycode == KEY_D)
        game->keys.d = 0;
    else if (keycode == KEY_LEFT)
        game->keys.left = 0;
    else if (keycode == KEY_RIGHT)
        game->keys.right = 0;
    
    return 0;
}

void update_player_position(t_game *game)
{
    double new_x, new_y;
    
    
    if (game->keys.left)
        game->player.dir -= game->player.rot_speed;
    if (game->keys.right)
        game->player.dir += game->player.rot_speed;
    
    
    if (game->player.dir < 0)
        game->player.dir += 2 * PI;
    if (game->player.dir >= 2 * PI)
        game->player.dir -= 2 * PI;
    

    if (game->keys.w)
    {
        new_x = game->player.x + cos(game->player.dir) * game->player.move_speed;
        new_y = game->player.y + sin(game->player.dir) * game->player.move_speed;
        
    
        if (game->map.map[(int)new_y][(int)new_x] != '1')
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    
    if (game->keys.s)
    {
        new_x = game->player.x - cos(game->player.dir) * game->player.move_speed;
        new_y = game->player.y - sin(game->player.dir) * game->player.move_speed;
        
     
        if (game->map.map[(int)new_y][(int)new_x] != '1')
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    
   
    if (game->keys.a)
    {
        new_x = game->player.x + cos(game->player.dir - PI/2) * game->player.move_speed;
        new_y = game->player.y + sin(game->player.dir - PI/2) * game->player.move_speed;
        
     
        if (game->map.map[(int)new_y][(int)new_x] != '1')
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    
    if (game->keys.d)
    {
        new_x = game->player.x + cos(game->player.dir + PI/2) * game->player.move_speed;
        new_y = game->player.y + sin(game->player.dir + PI/2) * game->player.move_speed;
        
    
        if (game->map.map[(int)new_y][(int)new_x] != '1')
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
}

int main_loop(t_game *game)
{
 
    update_player_position(game);
    

    render_floor_celling(game);
    
 
    perform_raycasting(game);
    
 
    mlx_put_image_to_window(game->mlx, game->win, game->image.new_image, 0, 0);
    return 0;
}

void cleanup_textures(t_game *game)
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

void cleanup_map(t_game *game)
{
    int i;
    
    if (game->map.map)
    {
        i = 0;
        while (game->map.map[i])
        {
            free(game->map.map[i]);
            i++;
        }
        free(game->map.map);
        game->map.map = NULL;
    }
}

int close_window(t_game *game)
{
  
    cleanup_textures(game);
    

    cleanup_map(game);
    
  
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
    
    exit(0);
    return 0;
}