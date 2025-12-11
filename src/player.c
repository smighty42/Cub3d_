#include "../mlx/mlx.h"
#include "../cub3d.h"
#include <stdio.h>

void put_player(t_game *game)
{
    int i=0;
    int j;
    char c;
    while(i<game->map.height)
    {
        j=0;
        while(j<game->map.width)
        {
            c = game->map.map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                game->player.x = j + 0.5; 
                game->player.y = i + 0.5;

                if (c == 'N')
                    game->player.angle_eye = 3.0 * PI / 2;  
                else if (c == 'S')
                    game->player.angle_eye = PI / 2;    
                else if (c == 'E')
                    game->player.angle_eye = 0.0;       
                else if (c == 'W')
                    game->player.angle_eye = PI;         
            }
            j++;
        }
        i++;
    }    
}