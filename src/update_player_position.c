/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:10:28 by smayti            #+#    #+#             */
/*   Updated: 2026/01/08 12:39:06 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdlib.h>

void	update_key_w(t_game *game, double new_x, double new_y)
{
	if (game->keys.w)
	{
		new_x = game->player.x + cos(game->player.dir)
			* game->player.move_speed;
		new_y = game->player.y + sin(game->player.dir)
			* game->player.move_speed;
		if (game->map.map[(int)new_y][(int)new_x] != '1')
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
}

void	update_key_s(t_game *game, double new_x, double new_y)
{
	if (game->keys.s)
	{
		new_x = game->player.x - cos(game->player.dir)
			* game->player.move_speed;
		new_y = game->player.y - sin(game->player.dir)
			* game->player.move_speed;
		if (game->map.map[(int)new_y][(int)new_x] != '1')
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
}

void	update_key_a(t_game *game, double new_x, double new_y)
{
	if (game->keys.a)
	{
		new_x = game->player.x + cos(game->player.dir - PI / 2)
			* game->player.move_speed;
		new_y = game->player.y + sin(game->player.dir - PI / 2)
			* game->player.move_speed;
		if (game->map.map[(int)new_y][(int)new_x] != '1')
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
}

void	update_key_d(t_game *game, double new_x, double new_y)
{
	if (game->keys.d)
	{
		new_x = game->player.x + cos(game->player.dir + PI / 2)
			* game->player.move_speed;
		new_y = game->player.y + sin(game->player.dir + PI / 2)
			* game->player.move_speed;
		if (game->map.map[(int)new_y][(int)new_x] != '1')
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
}

void	update_player_position(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = 0;
	new_y = 0;
	if (game->keys.left)
		game->player.dir -= game->player.rot_speed;
	if (game->keys.right)
		game->player.dir += game->player.rot_speed;
	if (game->player.dir < 0)
		game->player.dir += 2 * PI;
	if (game->player.dir >= 2 * PI)
		game->player.dir -= 2 * PI;
	update_key_w(game, new_x, new_y);
	update_key_s(game, new_x, new_y);
	update_key_a(game, new_x, new_y);
	update_key_d(game, new_x, new_y);
}
