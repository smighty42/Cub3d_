/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:34:46 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/13 14:30:15 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_cub_file(t_game *game, char *filename)
{
	char	**lines;
	int		map_start;
	int		tex_count;

	if (check_file_ext(filename) != 0)
	{
		free_exit(game, "File must have .cub extension");
	}
	lines = read_file_lines(filename, &game->gc);
	if (!lines)
	{
		free_exit(game, "Failed to read file");
	}
	tex_count = parse_elements(game, lines);
	if (tex_count == -1 || tex_count != 6)
	{
		if (tex_count != -1)
			free_exit(game, "Missing texture or color info");
	}
	map_start = find_map_start(lines);
	if (map_start == -1)
		free_exit(game, "No map found");
	if (parse_map_data(game, lines, map_start) != 0)
		free_exit(game, "Map parsing failed");
}
