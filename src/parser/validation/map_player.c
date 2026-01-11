/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:30:45 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/11 15:40:06 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	set_player_dir(t_game *game, char dir)
{
	if (dir == 'N')
		game->player.dir = 3 * PI / 2;
	else if (dir == 'S')
		game->player.dir = PI / 2;
	else if (dir == 'E')
		game->player.dir = 0;
	else if (dir == 'W')
		game->player.dir = PI;
}

static void	init_player_pos(t_game *game, int y, int x, char dir)
{
	game->player.x = (double)x + 0.5;
	game->player.y = (double)y + 0.5;
	set_player_dir(game, dir);
	game->player.move_speed = 0.1;
	game->player.rot_speed = 0.05;
}

int	find_and_init_player(t_game *game)
{
	int		i;
	int		j;
	char	player_dir;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (is_player_char(game->map.map[i][j]))
			{
				player_dir = game->map.map[i][j];
				init_player_pos(game, i, j, player_dir);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (-1);
}
