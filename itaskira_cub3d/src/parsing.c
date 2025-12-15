#include "../include/cub3d.h"

static int	count_lines(char *filename)
{
	int		fd;
	char	*line;
	int		count = 0;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

static char	**read_file_lines(char *filename)
{
	int		fd;
	char	*line;
	char	**lines;
	int		line_count;
	int		i;

	line_count = count_lines(filename);
	if (line_count <= 0)
		return (NULL);
	
	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		return (NULL);
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(lines);
		return (NULL);
	}
	
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		lines[i] = ft_strtrim(line, "\n");
		free(line);
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

static int	find_map_start(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] && (lines[i][j] == ' ' || lines[i][j] == '\t'))
			j++;
		if (lines[i][j] == '1' || lines[i][j] == '0')
			return (i);
		i++;
	}
	return (-1);
}

int	parse_file(t_game *game, char *filename)
{
	char	**lines;
	int		i;
	int		map_start;
	int		texture_count = 0;

	// Check file extension
	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".cub", 4) != 0)
		return (error_exit("Error: File must have .cub extension"), -1);
	
	lines = read_file_lines(filename);
	if (!lines)
		return (error_exit("Error: Failed to read file"), -1);
	
	// Parse textures and colors
	i = 0;
	while (lines[i] && texture_count < 6)
	{
		if (lines[i][0] && lines[i][0] != ' ' && lines[i][0] != '\t' &&
			lines[i][0] != '1' && lines[i][0] != '0')
		{
			if (parse_textures(game, lines[i]) == 0 ||
				parse_colors(game, lines[i]) == 0)
				texture_count++;
		}
		i++;
	}
	
	if (texture_count != 6)
		return (error_exit("Error: Missing texture or color information"), -1);
	
	// Find and parse map
	map_start = find_map_start(lines);
	if (map_start == -1)
		return (error_exit("Error: No valid map found"), -1);
	
	if (parse_map(game, lines, map_start) != 0)
	{
		// Free lines before returning
		i = 0;
		while (lines[i])
			free(lines[i++]);
		free(lines);
		return (-1);
	}
	
	// Free lines
	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
	
	return (0);
}

int	parse_textures(t_game *game, char *line)
{
	char	**split;

	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		split = ft_split(line, ' ');
		if (!split || !split[1])
			return (-1);
		game->north_path = ft_strdup(split[1]);
		// Free split array
		int i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		return (0);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		split = ft_split(line, ' ');
		if (!split || !split[1])
			return (-1);
		game->south_path = ft_strdup(split[1]);
		// Free split array
		int i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		return (0);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		split = ft_split(line, ' ');
		if (!split || !split[1])
			return (-1);
		game->west_path = ft_strdup(split[1]);
		// Free split array
		int i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		return (0);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		split = ft_split(line, ' ');
		if (!split || !split[1])
			return (-1);
		game->east_path = ft_strdup(split[1]);
		// Free split array
		int i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		return (0);
	}
	return (-1);
}

static int	parse_rgb(char *rgb_str)
{
	char	**rgb_split;
	int		r, g, b;
	int		color;
	int		i;

	rgb_split = ft_split(rgb_str, ',');
	if (!rgb_split || !rgb_split[0] || !rgb_split[1] || !rgb_split[2])
		return (-1);
	
	r = ft_atoi(rgb_split[0]);
	g = ft_atoi(rgb_split[1]);
	b = ft_atoi(rgb_split[2]);
	
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		i = 0;
		while (rgb_split[i])
			free(rgb_split[i++]);
		free(rgb_split);
		return (-1);
	}
	
	color = (r << 16) | (g << 8) | b;
	
	i = 0;
	while (rgb_split[i])
		free(rgb_split[i++]);
	free(rgb_split);
	
	return (color);
}

int	parse_colors(t_game *game, char *line)
{
	char	**split;
	int		color;
	int		i;

	if (ft_strncmp(line, "F ", 2) == 0)
	{
		split = ft_split(line, ' ');
		if (!split || !split[1])
			return (-1);
		color = parse_rgb(split[1]);
		if (color == -1)
		{
			i = 0;
			while (split[i])
				free(split[i++]);
			free(split);
			return (-1);
		}
		if (!game->textures)
		{
			game->textures = malloc(sizeof(t_texture));
			memset(game->textures, 0, sizeof(t_texture));
		}
		game->textures->floor_color = color;
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		return (0);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		split = ft_split(line, ' ');
		if (!split || !split[1])
			return (-1);
		color = parse_rgb(split[1]);
		if (color == -1)
		{
			i = 0;
			while (split[i])
				free(split[i++]);
			free(split);
			return (-1);
		}
		if (!game->textures)
		{
			game->textures = malloc(sizeof(t_texture));
			memset(game->textures, 0, sizeof(t_texture));
		}
		game->textures->ceiling_color = color;
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		return (0);
	}
	return (-1);
}

int	parse_map(t_game *game, char **lines, int start_idx)
{
	int	i;
	int	map_height = 0;
	int	max_width = 0;
	int	current_width;

	// Calculate map dimensions
	i = start_idx;
	while (lines[i])
	{
		current_width = ft_strlen(lines[i]);
		if (current_width > max_width)
			max_width = current_width;
		map_height++;
		i++;
	}
	
	game->map_height = map_height;
	game->map_width = max_width;
	
	// Allocate map
	game->map = malloc(sizeof(char *) * (map_height + 1));
	if (!game->map)
		return (error_exit("Error: Failed to allocate map"), -1);
	
	// Copy map lines
	i = 0;
	while (i < map_height)
	{
		game->map[i] = ft_strdup(lines[start_idx + i]);
		if (!game->map[i])
			return (error_exit("Error: Failed to allocate map line"), -1);
		i++;
	}
	game->map[i] = NULL;
	
	return (0);
}