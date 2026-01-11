/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:31:00 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/11 15:43:36 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static int	validate_rgb_parts(char **rgb)
{
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
	return (0);
}

int	parse_rgb(char **rgb, t_color *color)
{
	int	r;
	int	g;
	int	b;

	if (validate_rgb_parts(rgb) != 0)
		return (-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (check_rgb_values(r, g, b) != 0)
		return (-1);
	color->r = r;
	color->g = g;
	color->b = b;
	color->rgb = (r << 16) | (g << 8) | b;
	return (0);
}

int	parse_rgb_color(char *rgb_str, t_color *color, t_gc **gc)
{
	char	**rgb;
	int		result;

	if (!is_valid_rgb_format(rgb_str))
		return (-1);
	rgb = ft_split_gc(rgb_str, ',', gc);
	result = parse_rgb(rgb, color);
	return (result);
}

static int	assign_color(t_game *game, char *line, char **split)
{
	int	result;

	result = -1;
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (game->floor_color.rgb != -1)
			free_exit(game, "Duplicate F (floor) color definition");
		result = parse_rgb_color(split[1], &game->floor_color, &game->gc);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (game->ceiling_color.rgb != -1)
			free_exit(game, "Duplicate C (ceiling) color definition");
		result = parse_rgb_color(split[1], &game->ceiling_color, &game->gc);
	}
	return (result);
}

int	parse_color_line(t_game *game, char *line)
{
	char	**split;
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
	return (assign_color(game, line, split));
}
