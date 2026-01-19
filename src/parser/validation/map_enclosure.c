/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_enclosure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:30:38 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/13 15:38:57 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	check_enclosed_map(t_game *game)
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
