#include "../mlx/mlx.h"
#include "../cub3d.h"
#include <stdio.h>
#include <stdlib.h>


void init(t_game *game)
{
    game->width = WIN_WIDTH;
    game->height = WIN_HEIGHT;
    game->mlx = mlx_init();
    if(!game->mlx)
        printf("error mlx");
    game->win = mlx_new_window(game->mlx, game->width, game->height, "cub3d");
    if(!game->win)
        printf("error win");
}
void put_celling_floor(t_game *game)
{
   game->image.new_image=mlx_new_image(game->mlx,game->width,game->height);
   game->image.add=mlx_get_data_addr(game->image.new_image,&game->image.pixel_bit,&game->image.line_length_byte,&game->image.endian);
}
void init_game(t_game *game,char *file)
{
  
    game->keys.w = 0;
    game->keys.s = 0;
    game->keys.a = 0;
    game->keys.d = 0;
    game->keys.left = 0;
    game->keys.right = 0;
    
    //map parse ör:parse_cub(file,game);
    fake_parse_cub(game,file);
    init(game);
    put_celling_floor(game);
    

    load_textures(game);
}


int main(int ac, char **av)
{
    t_game game;
    (void)ac;
    

    
  //  if(ac != 2)
  //    return(1); //hata mesajı
    init_game(&game,av[1]);
    
    // Hook'ları ayarla
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);  
    mlx_hook(game.win, 3, 1L<<1, key_release, &game); 
    mlx_hook(game.win, 17, 1L<<17, close_window, &game); 
    mlx_loop_hook(game.mlx, main_loop, &game);       

    
    mlx_loop(game.mlx);
    
    return 0;
} 