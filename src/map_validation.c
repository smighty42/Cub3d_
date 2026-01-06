#include "../cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_map_chars(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (!is_valid_char(game->map.map[i][j]))
				return (-1);
			if (is_player_char(game->map.map[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (-1);
	return (0);
}

static int	check_first_last(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.map[0][i])
	{
		if (game->map.map[0][i] != '1' && game->map.map[0][i] != ' ')
			return (-1);
		i++;
	}
	i = 0;
	while (game->map.map[game->map.height - 1][i])
	{
		if (game->map.map[game->map.height - 1][i] != '1'
			&& game->map.map[game->map.height - 1][i] != ' ')
			return (-1);
		i++;
	}
	return (0);
}

static int	check_border_walls(t_game *game)
{
	int	j;
	int	len;
	int	last_char_idx;

	if (check_first_last(game) != 0)
		return (-1);
	j = 0;
	while (j < game->map.height)
	{
		if (game->map.map[j][0] != '1' && game->map.map[j][0] != ' ')
			return (-1);
		len = ft_strlen(game->map.map[j]);
		if (len > 0)
		{
			last_char_idx = len - 1;
			while (last_char_idx >= 0 && game->map.map[j][last_char_idx] == ' ')
				last_char_idx--;
			if (last_char_idx >= 0 && game->map.map[j][last_char_idx] != '1')
				return (-1);
		}
		j++;
	}
	return (0);
}

static int	check_top_bottom(t_game *game, int y, int x)
{
	if (y > 0 && x < ft_strlen(game->map.map[y - 1]))
		if (game->map.map[y - 1][x] == '0' || is_player_char(game->map.map[y
				- 1][x]))
			return (-1);
	if (y < game->map.height - 1 && x < ft_strlen(game->map.map[y + 1]))
		if (game->map.map[y + 1][x] == '0' || is_player_char(game->map.map[y
				+ 1][x]))
			return (-1);
	return (0);
}

static int	check_left_right(t_game *game, int y, int x)
{
	if (x > 0)
		if (game->map.map[y][x - 1] == '0' || is_player_char(game->map.map[y][x
				- 1]))
			return (-1);
	if (x < ft_strlen(game->map.map[y]) - 1)
		if (game->map.map[y][x + 1] == '0' || is_player_char(game->map.map[y][x
				+ 1]))
			return (-1);
	return (0);
}

static int	check_space_neighbors(t_game *game, int y, int x)
{
	if (check_top_bottom(game, y, x) != 0)
		return (-1);
	if (check_left_right(game, y, x) != 0)
		return (-1);
	return (0);
}

static int	is_valid_neighbor(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map.height)
		return (0);
	if (x < 0 || x >= ft_strlen(game->map.map[y]))
		return (0);
	if (game->map.map[y][x] == ' ')
		return (0);
	return (1);
}

static int	check_playable_cell(t_game *game, int y, int x)
{
	if (!is_valid_neighbor(game, y - 1, x))
		return (-1);
	if (!is_valid_neighbor(game, y + 1, x))
		return (-1);
	if (!is_valid_neighbor(game, y, x - 1))
		return (-1);
	if (!is_valid_neighbor(game, y, x + 1))
		return (-1);
	return (0);
}

static int	check_enclosed_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < ft_strlen(game->map.map[y]))
		{
			if (game->map.map[y][x] == ' ')
			{
				if (check_space_neighbors(game, y, x) != 0)
					return (-1);
			}
			else if (game->map.map[y][x] == '0'
				|| is_player_char(game->map.map[y][x]))
			{
				if (check_playable_cell(game, y, x) != 0)
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static void	set_player_dir(t_game *game, char dir)
{
	if (dir == 'N')
		game->player.dir = 3 * PI / 2;
	else if (dir == 'S')
		game->player.dir = PI / 2;
	else if (dir == 'E')
		game->player.dir = 0;
	else if (dir == 'W')
		game->player.dir = PI;
}

static void	init_player_pos(t_game *game, int y, int x, char dir)
{
	game->player.x = (double)x + 0.5;
	game->player.y = (double)y + 0.5;
	set_player_dir(game, dir);
	game->player.move_speed = 0.1;
	game->player.rot_speed = 0.05;
}

int	find_and_init_player(t_game *game)
{
	int		i;
	int		j;
	char	player_dir;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (is_player_char(game->map.map[i][j]))
			{
				player_dir = game->map.map[i][j];
				init_player_pos(game, i, j, player_dir);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

int	validate_map(t_game *game)
{
	if (check_map_chars(game) != 0)
	{
		printf("Error: Invalid characters in map\n");
		return (-1);
	}
	if (check_border_walls(game) != 0)
	{
		printf("Error: Map borders not enclosed\n");
		return (-1);
	}
	if (check_enclosed_map(game) != 0)
	{
		printf("Error: Map not properly enclosed\n");
		return (-1);
	}
	if (find_and_init_player(game) != 0)
	{
		printf("Error: Player position not found\n");
		return (-1);
	}
	return (0);
}
