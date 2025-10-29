#include "../minilibx/mlx.h"
#include "../cub3d.h"
#include <stdio.h>
#include <stdlib.h>
void init(t_game *game)
{
    game->width=1280;
    game->height=720;
    game->mlx=mlx_init();
    if(!game->mlx)
        printf("error mlx");
    game->win=mlx_new_window(game->mlx,game->width,game->height,"cub3d");
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
    //ft_bzero(game,sizeof(t_game));
    //map parse ör:parse_cub(file,game);
    fake_parse_cub(game,file);
    init(game);
    put_celling_floor(game);

}


int main(int ac, char **av)
{
    t_game game;
    (void)ac;
  //  if(ac != 2)
  //    return(1); //hata mesajı
    init_game(&game,av[1]);
    put_player(&game);
    render_floor_celling(&game);
    mlx_loop(game.mlx);
    
} 