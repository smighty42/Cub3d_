#include "../cub3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int	count_lines(char *filename)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
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
	while (i < line_count)
	{
		line = get_next_line(fd);
		lines[i] = ft_strtrim(line, "\n");
		free(line);
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	parse_texture_line(t_game *game, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split || !split[1])
		return (-1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->texture.north = ft_strdup(split[1]);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->texture.south = ft_strdup(split[1]);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->texture.west = ft_strdup(split[1]);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->texture.east = ft_strdup(split[1]);
	else
	{
		free_split(split);
		return (-1);
	}
	free_split(split);
	return (0);
}

static int	parse_rgb_color(char *rgb_str, t_color *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(rgb_str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	color->r = r;
	color->g = g;
	color->b = b;
	color->rgb = (r << 16) | (g << 8) | b;
	return (0);
}

static int	parse_color_line(t_game *game, char *line)
{
	char	**split;
	int		result;

	split = ft_split(line, ' ');
	if (!split || !split[1])
		return (-1);
	if (ft_strncmp(line, "F ", 2) == 0)
		result = parse_rgb_color(split[1], &game->floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0)
		result = parse_rgb_color(split[1], &game->ceiling_color);
	else
	{
		free_split(split);
		return (-1);
	}
	free_split(split);
	return (result);
}

static int	is_texture_or_color(char *line)
{
	if (!line || !line[0])
		return (0);
	if (line[0] == ' ' || line[0] == '\t')
		return (0);
	if (line[0] == '1' || line[0] == '0')
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (2);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (2);
	return (0);
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

static int	parse_map_data(t_game *game, char **lines, int start)
{
	int	h;
	int	max_w;
	int	i;

	h = 0;
	max_w = 0;
	while (lines[start + h])
	{
		if (ft_strlen(lines[start + h]) > max_w)
			max_w = ft_strlen(lines[start + h]);
		h++;
	}
	game->map.height = h;
	game->map.width = max_w;
	game->map.map = malloc(sizeof(char *) * (h + 1));
	if (!game->map.map)
		return (-1);
	i = 0;
	while (i < h)
	{
		game->map.map[i] = ft_strdup(lines[start + i]);
		if (!game->map.map[i])
			return (-1);
		i++;
	}
	game->map.map[i] = NULL;
	return (0);
}

void	parse_cub_file(t_game *game, char *filename)
{
	char	**lines;
	int		i;
	int		map_start;
	int		tex_count;

	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".cub", 4) != 0)
	{
		printf("Error: File must have .cub extension\n");
		return ;
	}
	lines = read_file_lines(filename);
	if (!lines)
	{
		printf("Error: Failed to read file\n");
		return ;
	}
	i = 0;
	tex_count = 0;
	while (lines[i] && tex_count < 6)
	{
		if (is_texture_or_color(lines[i]) == 1)
		{
			if (parse_texture_line(game, lines[i]) == 0)
				tex_count++;
		}
		else if (is_texture_or_color(lines[i]) == 2)
		{
			if (parse_color_line(game, lines[i]) == 0)
				tex_count++;
		}
		i++;
	}
	if (tex_count != 6)
	{
		printf("Error: Missing texture or color info\n");
		free_split(lines);
		return ;
	}
	map_start = find_map_start(lines);
	if (map_start == -1)
	{
		printf("Error: No valid map found\n");
		free_split(lines);
		return ;
	}
	if (parse_map_data(game, lines, map_start) != 0)
	{
		printf("Error: Failed to parse map\n");
		free_split(lines);
		return ;
	}
	free_split(lines);
}
