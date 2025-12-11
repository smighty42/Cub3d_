#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cub3d.h"
#include "../mlx/mlx.h"

void load_textures(t_game *game)
{
    int width, height;

    // Texture'ları yükle
    game->texture.north_img = mlx_xpm_file_to_image(game->mlx, game->texture.north, &width, &height);
    game->texture.south_img = mlx_xpm_file_to_image(game->mlx, game->texture.south, &width, &height);
    game->texture.east_img = mlx_xpm_file_to_image(game->mlx, game->texture.east, &width, &height);
    game->texture.west_img = mlx_xpm_file_to_image(game->mlx, game->texture.west, &width, &height);

    // Hata kontrolü
    if (!game->texture.north_img)
        printf("Warning: Could not load north texture: %s\n", game->texture.north);
    if (!game->texture.south_img)
        printf("Warning: Could not load south texture: %s\n", game->texture.south);
    if (!game->texture.east_img)
        printf("Warning: Could not load east texture: %s\n", game->texture.east);
    if (!game->texture.west_img)
        printf("Warning: Could not load west texture: %s\n", game->texture.west);
}
void fake_parse_cub(t_game *game, char *file)
{
    (void)file;

    // --- Texture yolları (basit XPM dosyaları kullanacağız)
    game->texture.north = "./textures/wall_red.xpm";
    game->texture.south = "./textures/wall_blue.xpm";  
    game->texture.east  = "./textures/wall_green.xpm";
    game->texture.west  = "./textures/wall_yellow.xpm";

    // --- Zemin ve tavan renkleri
    game->floor_color.r = 139;
    game->floor_color.g = 69;
    game->floor_color.b = 19;

    game->ceiling_color.r = 135;
    game->ceiling_color.g = 206;
    game->ceiling_color.b = 235;

    // --- Basit sahte map
char *tmp_map[] = {
    "11111111111111111",
    "10000000000000001",
    "100N0000001111111",
    "10000000001",
    "10000000001111111",
    "10000001100000001",
    "10000000000000001",
    "11111111111111111",
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
    game->player.x = 3.5;
    game->player.y = 2.5;

    game->player.dir = 3 * PI /2;    // N (kuzey) yönüne bakıyor
    game->player.move_speed = 0.1;    // ileri/geri hareket hızı
    game->player.rot_speed = 0.05;    // dönme hızı

    printf("Fake map parse completed.\n");
}
