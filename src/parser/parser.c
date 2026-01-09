
#include "../cub3d.h"
#include "../get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	count_lines(char *filename, t_gc **gc)
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
		line = get_next_line(fd, gc);
		if (!line)
			break ;
		count++;
	}
	close(fd);
	return (count);
}

static char	**alloc_lines(char *filename, int *line_count, t_gc **gc)
{
	char	**lines;
	int		fd;

	*line_count = count_lines(filename, gc);
	if (*line_count <= 0)
		return (NULL);
	lines = gc_malloc(gc, sizeof(char *) * (*line_count + 1));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	return (lines);
}

static char	**read_file_lines(char *filename, t_gc **gc)
{
	int		fd;
	char	*line;
	char	**lines;
	int		line_count;
	int		i;

	lines = alloc_lines(filename, &line_count, gc);
	if (!lines || line_count == 0)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	while (i < line_count)
	{
		line = get_next_line(fd, gc);
		if (!line)
			break ;
		lines[i] = ft_strtrim_gc(line, "\n", gc);
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

void	free_split(char **split)
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

static int	check_file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

static int	set_texture(t_game *game, char *line, char **split)
{
	if (check_file_exists(split[1]) != 0)
	{
		free_exit(game, "Texture file not found.\n");
		return (-1);
	}
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (game->texture.north != NULL)
		{
			free_exit(game, "Duplicate NO texture definition.\n");
		}
		game->texture.north = ft_strdup_gc(split[1], &game->gc);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (game->texture.south != NULL)
		{
			free_exit(game, "Duplicate SO texture definition.\n");
		}
		game->texture.south = ft_strdup_gc(split[1], &game->gc);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (game->texture.west != NULL)
		{
			free_exit(game, "Duplicate WE texture definition.\n");
		}
		game->texture.west = ft_strdup_gc(split[1], &game->gc);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (game->texture.east != NULL)
		{
			free_exit(game, "Duplicate EA texture definition.\n");
		}
		game->texture.east = ft_strdup_gc(split[1], &game->gc);
	}
	else
		return (-1);
	return (0);
}

static int	parse_texture_line(t_game *game, char *line)
{
	char	**split;
	int		result;
	int		count;

	split = ft_split_gc(line, ' ', &game->gc);
	if (!split || !split[1])
		return (-1);
	count = 0;
	while (split[count])
		count++;
	if (count != 2)
		return (-1);
	if (!split[1][0])
		return (-1);
	result = set_texture(game, line, split);
	return (result);
}

static int	is_valid_number(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_rgb(char **rgb, t_color *color)
{
	int	r;
	int	g;
	int	b;
	int	count;

	count = 0;
	while (rgb && rgb[count])
	{
		if (!rgb[count][0])
			return (-1);
		count++;
	}
	if (count != 3)
		return (-1);
	if (!is_valid_number(rgb[0]) || !is_valid_number(rgb[1])
		|| !is_valid_number(rgb[2]))
		return (-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	color->r = r;
	color->g = g;
	color->b = b;
	color->rgb = (r << 16) | (g << 8) | b;
	return (0);
}

static int	is_valid_rgb_format(char *str)
{
	int	i;
	int	comma_count;

	if (!str || !str[0])
		return (0);
	if (str[0] == ',')
		return (0);
	i = 0;
	comma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			comma_count++;
			if (str[i + 1] == ',' || str[i + 1] == '\0')
				return (0);
		}
		i++;
	}
	if (comma_count != 2)
		return (0);
	return (1);
}

static int	parse_rgb_color(char *rgb_str, t_color *color, t_gc **gc)
{
	char	**rgb;
	int		result;

	if (!is_valid_rgb_format(rgb_str))
		return (-1);
	rgb = ft_split_gc(rgb_str, ',', gc);
	result = parse_rgb(rgb, color);
	return (result);
}

static int	parse_color_line(t_game *game, char *line)
{
	char	**split;
	int		result;
	int		count;

	split = ft_split_gc(line, ' ', &game->gc);
	if (!split || !split[1])
		return (-1);
	count = 0;
	while (split[count])
		count++;
	if (count != 2)
		return (-1);
	if (!split[1][0])
		return (-1);
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (game->floor_color.rgb != -1)
		{
			free_exit(game, "Duplicate F (floor) color definition.\n");
		}
		result = parse_rgb_color(split[1], &game->floor_color, &game->gc);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (game->ceiling_color.rgb != -1)
		{
			free_exit(game, "Duplicate C (ceiling) color definition.\n");
		}
		result = parse_rgb_color(split[1], &game->ceiling_color, &game->gc);
	}
	else
		return (-1);
	return (result);
}

static int	check_identifier(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len >= 2 && ft_strncmp(line, "NO", 2) == 0)
	{
		if (len == 2 || line[2] == ' ' || line[2] == '\t')
			return (1);
	}
	if (len >= 2 && ft_strncmp(line, "SO", 2) == 0)
	{
		if (len == 2 || line[2] == ' ' || line[2] == '\t')
			return (1);
	}
	if (len >= 2 && ft_strncmp(line, "WE", 2) == 0)
	{
		if (len == 2 || line[2] == ' ' || line[2] == '\t')
			return (1);
	}
	if (len >= 2 && ft_strncmp(line, "EA", 2) == 0)
	{
		if (len == 2 || line[2] == ' ' || line[2] == '\t')
			return (1);
	}
	if (len >= 1 && line[0] == 'F')
	{
		if (len == 1 || line[1] == ' ' || line[1] == '\t')
			return (2);
	}
	if (len >= 1 && line[0] == 'C')
	{
		if (len == 1 || line[1] == ' ' || line[1] == '\t')
			return (2);
	}
	return (0);
}

static int	is_texture_or_color(char *line)
{
	if (!line || !line[0])
		return (0);
	if (line[0] == ' ' || line[0] == '\t')
		return (0);
	if (line[0] == '1' || line[0] == '0')
		return (0);
	return (check_identifier(line));
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

static int	get_map_size(char **lines, int start, int *h, int *max_w)
{
	int	len;

	*h = 0;
	*max_w = 0;
	while (lines[start + *h])
	{
		len = ft_strlen(lines[start + *h]);
		if (len > *max_w)
			*max_w = len;
		(*h)++;
	}
	return (0);
}

static int	parse_map_data(t_game *game, char **lines, int start)
{
	int	h;
	int	max_w;
	int	i;
	get_map_size(lines, start, &h, &max_w);
	game->map.height = h;
	game->map.width = max_w;
	game->map.map = gc_malloc(&game->gc, sizeof(char *) * (h + 1));
	if (!game->map.map)
		return (-1);
	i = 0;
	while (i < h)
	{
		game->map.map[i] = ft_strdup_gc(lines[start + i], &game->gc);
		if (!game->map.map[i])
			return (-1);
		i++;
	}
	game->map.map[i] = NULL;
	return (0);
}

static int	parse_elements(t_game *game, char **lines)
{
	int	i;
	int	tex_count;
	int	type;

	i = 0;
	tex_count = 0;
	while (lines[i] && tex_count < 6)
	{
		type = is_texture_or_color(lines[i]);
		if (type == 1)
		{
			if (parse_texture_line(game, lines[i]) != 0)
			{
				free_exit(game, "Invalid texture line.\n");
				return (-1);
			}
			tex_count++;
		}
		else if (type == 2)
		{
			if (parse_color_line(game, lines[i]) != 0)
			{
				free_exit(game, "Invalid color line.%s\n");
				return (-1);
			}
			tex_count++;
		}
		i++;
	}
	return (tex_count);
}

static int	check_file_ext(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (-1);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (-1);
	return (0);
}

void	parse_cub_file(t_game *game, char *filename)
{
	char	**lines;
	int		map_start;
	int		tex_count;

	if (check_file_ext(filename) != 0)
	{
		free_exit(game, "File must have .cub extension.\n");
	}
	lines = read_file_lines(filename, &game->gc);
	if (!lines)
	{
		free_exit(game, "Failed to read file\n");
	}
	tex_count = parse_elements(game, lines);
	if (tex_count == -1 || tex_count != 6)
	{
		if (tex_count != -1)
			free_exit(game, "Missing texture or color info.\n");
	}
	map_start = find_map_start(lines);
	if (map_start == -1)
	{
		free_exit(game, "No map found.\n");
		return ;
	}
	if (parse_map_data(game, lines, map_start) != 0)
	{
		free_exit(game, "Map parsing failed.\n");
		return ;
	}
}
