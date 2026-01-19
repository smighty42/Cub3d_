/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:31:06 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/19 15:43:24 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	find_map_start(char **lines)
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

int	get_map_size(char **lines, int start, int *h, int *max_w)
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

int	parse_map_data(t_game *game, char **lines, int start)
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

static int	proc_elem(t_game *game, char *line, int *type)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	trimmed = &line[i];
	*type = is_texture_or_color(line);
	if (*type == 1)
	{
		if (parse_texture_line(game, trimmed) != 0)
		{
			free_exit(game, "Invalid texture line");
			return (-1);
		}
	}
	else if (*type == 2)
	{
		if (parse_color_line(game, trimmed) != 0)
		{
			free_exit(game, "Invalid color line");
			return (-1);
		}
	}
	return (0);
}

int	parse_elements(t_game *game, char **lines)
{
	int	i;
	int	j;
	int	tex_count;
	int	type;

	i = 0;
	tex_count = 0;
	while (lines[i])
	{
		if (proc_elem(game, lines[i], &type) != 0)
			return (-1);
		if (type == 1 || type == 2)
			tex_count++;
		else
		{
			j = 0;
			while (lines[i][j] && (lines[i][j] == ' ' || lines[i][j] == '\t'))
				j++;
			if (lines[i][j] == '1' || lines[i][j] == '0')
				break ;
			if((lines[i][j] != '\0'))
				free_exit(game, "Invalid line in file");
		}
		i++;
	}
	return (tex_count);
}
