#include "../include/cub3d.h"

void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player->x + move_x;
	new_y = game->player->y + move_y;
	map_x = (int)new_x;
	map_y = (int)game->player->y;
	if (map_y >= 0 && map_y < game->map_height
		&& map_x >= 0 && map_x < (int)ft_strlen(game->map[map_y])
		&& game->map[map_y][map_x] != '1')
		game->player->x = new_x;
	map_x = (int)game->player->x;
	map_y = (int)new_y;
	if (map_y >= 0 && map_y < game->map_height
		&& map_x >= 0 && map_x < (int)ft_strlen(game->map[map_y])
		&& game->map[map_y][map_x] != '1')
		game->player->y = new_y;
}

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(angle)
		- game->player->dir_y * sin(angle);
	game->player->dir_y = old_dir_x * sin(angle)
		+ game->player->dir_y * cos(angle);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(angle)
		- game->player->plane_y * sin(angle);
	game->player->plane_y = old_plane_x * sin(angle)
		+ game->player->plane_y * cos(angle);
}

static void	handle_movement(int keycode, t_game *game)
{
	double	move_x;
	double	move_y;

	if (keycode == KEY_W)
	{
		move_x = game->player->dir_x * MOVE_SPEED;
		move_y = game->player->dir_y * MOVE_SPEED;
		move_player(game, move_x, move_y);
	}
	else if (keycode == KEY_S)
	{
		move_x = -game->player->dir_x * MOVE_SPEED;
		move_y = -game->player->dir_y * MOVE_SPEED;
		move_player(game, move_x, move_y);
	}
	else if (keycode == KEY_A)
	{
		move_x = -game->player->plane_x * MOVE_SPEED;
		move_y = -game->player->plane_y * MOVE_SPEED;
		move_player(game, move_x, move_y);
	}
	else if (keycode == KEY_D)
	{
		move_x = game->player->plane_x * MOVE_SPEED;
		move_y = game->player->plane_y * MOVE_SPEED;
		move_player(game, move_x, move_y);
	}
}

static void	handle_rotation(int keycode, t_game *game)
{
	if (keycode == KEY_LEFT)
		rotate_player(game, ROT_SPEED);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, -ROT_SPEED);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		close_window(game);
		return (0);
	}
	handle_movement(keycode, game);
	handle_rotation(keycode, game);
	return (0);
}

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
