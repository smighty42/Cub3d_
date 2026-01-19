/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_neighbors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:30:42 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/13 15:38:57 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

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

int	check_space_neighbors(t_game *game, int y, int x)
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

int	check_playable_cell(t_game *game, int y, int x)
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
