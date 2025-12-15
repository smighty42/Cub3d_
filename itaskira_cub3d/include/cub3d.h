#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include "../minilibx/mlx.h"

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define TEXTURE_SIZE 64
# define MAP_SIZE 24

# define MOVE_SPEED 0.15
# define ROT_SPEED 0.05

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_texture
{
	t_img	*north;
	t_img	*south;
	t_img	*east;
	t_img	*west;
	int		floor_color;
	int		ceiling_color;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		*img;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	*player;
	t_texture	*textures;
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
}	t_game;

// Function prototypes
int		init_game(t_game *game);
int		init_mlx(t_game *game);
int		init_player(t_game *game);
int		init_textures(t_game *game);

int		parse_file(t_game *game, char *filename);
int		parse_textures(t_game *game, char *line);
int		parse_colors(t_game *game, char *line);
int		parse_map(t_game *game, char **lines, int start_idx);

int		validate_map(t_game *game);
int		check_walls(t_game *game);
int		find_player(t_game *game);

void	perform_raycasting(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	calculate_step_and_side_dist(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	calculate_distance(t_game *game, t_ray *ray);

int		render_frame(t_game *game);
void	draw_vertical_line(t_game *game, int x, t_ray *ray);
void	draw_ceiling_floor(t_game *game, int x, t_ray *ray);

int		key_press(int keycode, t_game *game);
int		close_window(t_game *game);
void	move_player(t_game *game, double move_x, double move_y);
void	rotate_player(t_game *game, double angle);

char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char const *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(char const *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_atoi(const char *str);

void	cleanup_game(t_game *game);
void	cleanup_textures(t_game *game);
void	cleanup_map(t_game *game);
void	error_exit(char *msg);

#endif
