#ifndef CUB3_D
#define CUB3_D

#define PI 3.14159265358979323846
typedef struct s_color
{
    int r;
    int g;
    int b;
    int rgb;
} t_color;


typedef struct s_textures
{
    char *north;
    char *south; // buralara haritadan okumadan gelen texture xpm yolları gelicek :D
    char *east;
    char *west;

} t_textures;


typedef struct s_map
{
    char **map; // map iki boyutlu da tutulucak ve kontrol edilicek 
    int width; //map genişliği sütun sayısı
    int height; // map yükseliği satır sayısı 
}t_map;


typedef struct s_player
{
    int x;
    int y;//konumlarım 
    int angle_eye; //bakış açım olucak değişebilir belki hayat
}t_player;

typedef struct s_raycast
{
    double ray_angle;
    double ray_x;
    double ray_y;
    double distance;
} t_raycast;

typedef struct s_new_image
{
    void *new_image;
    void *add;
    int pixel_bit;
    int line_length_byte;
    int endian; 

}t_new_image;

typedef struct s_game
{
    void *mlx;
    void *win;
    t_player player;
    t_textures texture;
    t_color floor_color;
    t_color ceiling_color;
    t_map map;
    t_new_image image;
    int width;
    int height;

}t_game;

void fake_parse_cub(t_game *game, char *file);
void render_floor_celling(t_game *game);
void put_player(t_game *game);
void my_put_pixel(t_game *game,int x,int y,int color);
void render_walls(t_game *game);
#endif