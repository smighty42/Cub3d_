/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayti <smayti@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:10:44 by smayti            #+#    #+#             */
/*   Updated: 2026/01/11 12:04:19 by smayti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../cub3d.h"
#include <stdio.h>

int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	// Harita sınırlarını kontrol ediyorum
	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_y >= game->map.height
		|| map_x >= game->map.width)
		return (0);
	// Merkez pozisyonu kontrol ediyorum
	if (game->map.map[map_y][map_x] == '1')
		return (0);
	// 4 köşeyi de kontrol ediyorum duvara sıfır mesafe ilerlemesin diye 
	if (game->map.map[(int)(y + WALL_BUFFER)][(int)(x + WALL_BUFFER)] == '1'
		|| game->map.map[(int)(y + WALL_BUFFER)][(int)(x - WALL_BUFFER)] == '1'
		|| game->map.map[(int)(y - WALL_BUFFER)][(int)(x + WALL_BUFFER)] == '1'
		|| game->map.map[(int)(y - WALL_BUFFER)][(int)(x - WALL_BUFFER)] == '1')
		return (0);
	return (1);
}

