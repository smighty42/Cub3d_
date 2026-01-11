/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira < itaskira@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:31:07 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/11 14:57:13 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <fcntl.h>
#include <unistd.h>

int	check_file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

static int	assign_texture(t_game *game, char *type, char *path)
{
	if (ft_strncmp(type, "NO ", 3) == 0)
	{
		if (game->texture.north != NULL)
			return (1);
		game->texture.north = ft_strdup_gc(path, &game->gc);
	}
	else if (ft_strncmp(type, "SO ", 3) == 0)
	{
		if (game->texture.south != NULL)
			return (1);
		game->texture.south = ft_strdup_gc(path, &game->gc);
	}
	else if (ft_strncmp(type, "WE ", 3) == 0)
	{
		if (game->texture.west != NULL)
			return (1);
		game->texture.west = ft_strdup_gc(path, &game->gc);
	}
	else if (ft_strncmp(type, "EA ", 3) == 0)
	{
		if (game->texture.east != NULL)
			return (1);
		game->texture.east = ft_strdup_gc(path, &game->gc);
	}
	return (0);
}

int	set_texture(t_game *game, char *line, char **split)
{
	if (check_file_exists(split[1]) != 0)
	{
		free_exit(game, "Texture file not found");
		return (-1);
	}
	if (assign_texture(game, line, split[1]) != 0)
	{
		free_exit(game, "Duplicate texture definition");
		return (-1);
	}
	return (0);
}

int	parse_texture_line(t_game *game, char *line)
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
