#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cub3d.h"
void fake_parse_cub(t_game *game, char *file)
{
    (void)file;

    // --- Texture yolları
    game->texture.north = "./textures/north.xpm";
    game->texture.south = "./textures/south.xpm";
    game->texture.east  = "./textures/east.xpm";
    game->texture.west  = "./textures/west.xpm";

    // --- Zemin ve tavan renkleri
    game->floor_color.r = 255;
    game->floor_color.g = 255;
    game->floor_color.b = 255;

    game->ceiling_color.r = 225;
    game->ceiling_color.g = 30;
    game->ceiling_color.b = 0;

    // --- Basit sahte map
    char *tmp_map[] = {
        "1111111111111",
        "1000000000001",
        "10N0010000001",
        "1000000000001",
        "1111111111111",
        NULL
    };

    int h = 0;
    while (tmp_map[h])
        h++;
    game->map.height = h;
    game->map.width = strlen(tmp_map[0]);

    game->map.map = malloc(sizeof(char *) * (h + 1));
    for (int i = 0; i < h; i++)
        game->map.map[i] = strdup(tmp_map[i]);
    game->map.map[h] = NULL;

    // --- Oyuncu konumu ve yönü
    game->player.x = 2.5;  // N karakterinin ortası
    game->player.y = 2.5;

    printf("Fake map parse completed.\n");
}
