/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:08:21 by smayti            #+#    #+#             */
/*   Updated: 2026/01/19 14:12:05 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# define WALL_BUFFER 0.3
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
	char		*east;
	char		*west;
	void		*north_img;
	void		*south_img;
	void		*east_img;
	void		*west_img;

}				t_textures;

typedef struct s_map
{
	char		**map;
	int			width;
	int			height;

}				t_map;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir;
	double		move_speed;
	double		rot_speed;

}				t_player;

typedef struct s_raycast
{
	double		ray_angle;
	double		ray_x;
	double		ray_y;
	double		distance;
	double		wall_x;
	int			hit_side;
	int			map_x;
	int			map_y;

	int			step_x;
	int			step_y;

	double		side_dist_x;
	double		side_dist_y;

	double		delta_dist_x;
	double		delta_dist_y;

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
void			parse_cub_file(t_game *game, char *filename);
int				validate_map(t_game *game);
void			free_exit(t_game *game, const char *message);
char			*get_next_line(int fd, t_gc **gc);
void			render_floor_celling(t_game *game);
void			my_put_pixel(t_game *game, int x, int y, int color);
void			perform_raycasting(t_game *game);
void			draw_wall_slice(t_game *game, int x, t_raycast ray);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				main_loop(t_game *game);
void			update_player_position(t_game *game);
int				close_window(t_game *game);
void			cleanup_textures(t_game *game);
void			clean(t_game *game);
void			load_textures(t_game *game);
int				is_valid_position(t_game *game, double x, double y);
void			ft_bzero(void *s, size_t n);

#endif
