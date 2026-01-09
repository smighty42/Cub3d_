#ifndef CUB3_D
# define CUB3_D

# define PI 3.141592653

# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define TEX_SIZE 64
# include <stddef.h>
typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			rgb;
}				t_color;

typedef struct s_textures
{
	char		*north;
	char		*south;
	// buralara haritadan okumadan gelen texture xpm yolları gelicek :D
	char		*east;
	char		*west;
	void		*north_img;
	void		*south_img;
	void		*east_img;
	void		*west_img;
	int			tex_width;
	int			tex_height;
}				t_textures;

typedef struct s_map
{
	char **map; // map iki boyutlu da tutulucak ve kontrol edilicek
	int width;  // map genişliği sütun sayısı
	int height; // map yükseliği satır sayısı
}				t_map;

typedef struct s_player
{
	double		x;
	double		y;
	double dir; // Radyan cinsinden yön açısı
	double		move_speed;
	double		rot_speed;
	double angle_eye; // bakış açım olucak değişebilir belki hayat
}				t_player;

typedef struct s_raycast
{
	double		ray_angle;
	double		ray_x;
	double		ray_y;
	double		distance;
	double		wall_x;
	int hit_side; // 0: NS duvarı, 1: EW duvarı
	int			map_x;
	int			map_y;

	int			step_x;
	int			step_y;

	double		side_dist_x;
	double		side_dist_y;

	double delta_dist_x, delta_dist_y;
}				t_raycast;

typedef struct s_dda
{
	int			hit;
	int			side;
}				t_dda;

typedef struct s_new_image
{
	void		*new_image;
	void		*add;
	int			pixel_bit;
	int			line_length_byte;
	int			endian;

}				t_new_image;

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;

typedef struct s_game
{
	t_keys		keys;

	void		*mlx;
	void		*win;
	t_player	player;
	t_textures	texture;
	t_color		floor_color;
	t_color		ceiling_color;
	t_map		map;
	t_new_image	image;
	int			width;
	int			height;

	t_gc		*gc;
}				t_game;

typedef struct s_texture_calc
{
	char		*data;
	int			bpp;
	int			line_len;
	int			endian;
	int			x;
	int			y;
	int			draw_start;
}				t_texture_calc;

void			*gc_malloc(t_gc **gc, size_t size);
void			gc_free_all(t_gc **gc);
void			gc_add(t_gc **gc, void *ptr);
char			*ft_strdup_gc(const char *s1, t_gc **gc);
char			*ft_strjoin_gc(const char *s1, const char *s2, t_gc **gc);
char			**ft_split_gc(char const *s, char c, t_gc **gc);
char			*ft_strtrim_gc(char const *s1, char const *set, t_gc **gc);
void			parse_cub_file(t_game *game, char *filename);
int				validate_map(t_game *game);
int				find_and_init_player(t_game *game);
void			free_split(char **split);
void			free_exit(t_game *game, const char *message);
int				ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, int n);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(const char *s1, const char *s2);
int				ft_atoi(const char *str);
char			*ft_strtrim(char const *s1, char const *set);
char			*get_next_line(int fd, t_gc **gc);
char			*ft_strchr(const char *s, int c);
void			render_floor_celling(t_game *game);
void			put_player(t_game *game);
void			my_put_pixel(t_game *game, int x, int y, int color);
void			render_walls(t_game *game);
void			perform_raycasting(t_game *game);
t_raycast		cast_ray(t_game *game, double angle);
void			draw_wall_slice(t_game *game, int x, t_raycast ray);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				main_loop(t_game *game);
void			update_player_position(t_game *game);
int				close_window(t_game *game);
void			cleanup_textures(t_game *game);
void			load_textures(t_game *game);
int				get_texture_color(t_game *game, t_raycast ray, int y,
					int wall_height);
void			ft_resetter(t_game *game);
#endif
