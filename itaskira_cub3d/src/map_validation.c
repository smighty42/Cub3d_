#include "../include/cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' ||
			c == 'S' || c == 'E' || c == 'W');
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_map_chars(t_game *game)
{
	int	i;
	int	j;
	int	player_count = 0;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_char(game->map[i][j]))
				return (error_exit("Error: Invalid character in map"), -1);
			if (is_player_char(game->map[i][j]))
				player_count++;
			j++;
		}
		i++;
	}

	if (player_count != 1)
		return (error_exit("Error: Map must have exactly one player"), -1);

	return (0);
}



static int	flood_fill_check(t_game *game, int x, int y, char **visited)
{
	// Check bounds
	if (y < 0 || y >= game->map_height || x < 0 || x >= (int)ft_strlen(game->map[y]))
		return (-1); // Out of bounds - not enclosed
	
	// If we hit a wall or already visited, return success
	if (game->map[y][x] == '1' || visited[y][x] == '1')
		return (0);
	
	// If we hit a space at the edge, map is not enclosed
	if (game->map[y][x] == ' ')
	{
		if (y == 0 || y == game->map_height - 1 || x == 0 || x >= (int)ft_strlen(game->map[y]) - 1)
			return (-1);
	}
	
	// Mark as visited
	visited[y][x] = '1';
	
	// Check all 4 directions
	if (flood_fill_check(game, x + 1, y, visited) == -1 ||
		flood_fill_check(game, x - 1, y, visited) == -1 ||
		flood_fill_check(game, x, y + 1, visited) == -1 ||
		flood_fill_check(game, x, y - 1, visited) == -1)
		return (-1);
	
	return (0);
}

static char	**create_visited_array(t_game *game)
{
	char	**visited;
	int		i;

	visited = malloc(sizeof(char *) * game->map_height);
	if (!visited)
		return (NULL);
	
	i = 0;
	while (i < game->map_height)
	{
		visited[i] = malloc(sizeof(char) * (ft_strlen(game->map[i]) + 1));
		if (!visited[i])
		{
			// Free allocated memory
			int j = 0;
			while (j < i)
				free(visited[j++]);
			free(visited);
			return (NULL);
		}
		memset(visited[i], '0', ft_strlen(game->map[i]));
		visited[i][ft_strlen(game->map[i])] = '\0';
		i++;
	}
	
	return (visited);
}

static void	free_visited_array(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(visited[i++]);
	free(visited);
}

int	check_walls(t_game *game)
{
	char	**visited;
	int		player_x, player_y;
	int		i, j;

	// Find player position
	i = 0;
	player_x = -1;
	player_y = -1;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (is_player_char(game->map[i][j]))
			{
				player_x = j;
				player_y = i;
				break;
			}
			j++;
		}
		if (player_x != -1)
			break;
		i++;
	}

	if (player_x == -1 || player_y == -1)
		return (error_exit("Error: Player not found"), -1);

	// Create visited array
	visited = create_visited_array(game);
	if (!visited)
		return (error_exit("Error: Failed to allocate visited array"), -1);

	// Perform flood fill from player position
	if (flood_fill_check(game, player_x, player_y, visited) == -1)
	{
		free_visited_array(visited, game->map_height);
		return (error_exit("Error: Map is not properly enclosed by walls"), -1);
	}

	free_visited_array(visited, game->map_height);
	return (0);
}

int	find_player(t_game *game)
{
	int	i;
	int	j;
	char	player_dir;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (is_player_char(game->map[i][j]))
			{
				player_dir = game->map[i][j];
				game->player->x = (double)j + 0.5;
				game->player->y = (double)i + 0.5;
				
				// Set initial direction based on player character
				if (player_dir == 'N')
				{
					game->player->dir_x = 0;
					game->player->dir_y = -1;
					game->player->plane_x = 0.66;
					game->player->plane_y = 0;
				}
				else if (player_dir == 'S')
				{
					game->player->dir_x = 0;
					game->player->dir_y = 1;
					game->player->plane_x = -0.66;
					game->player->plane_y = 0;
				}
				else if (player_dir == 'E')
				{
					game->player->dir_x = 1;
					game->player->dir_y = 0;
					game->player->plane_x = 0;
					game->player->plane_y = 0.66;
				}
				else if (player_dir == 'W')
				{
					game->player->dir_x = -1;
					game->player->dir_y = 0;
					game->player->plane_x = 0;
					game->player->plane_y = -0.66;
				}
				
				// Replace player character with empty space
				game->map[i][j] = '0';
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
	if (!game->map)
		return (error_exit("Error: No map found"), -1);
	
	if (check_map_chars(game) != 0)
		return (-1);
	
	if (check_walls(game) != 0)
		return (-1);
	
	return (0);
}