/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:30:48 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/13 15:38:59 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static int	check_first_last(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.map[0][i])
	{
		if (game->map.map[0][i] != '1' && game->map.map[0][i] != ' ')
			return (-1);
		i++;
	}
	i = 0;
	while (game->map.map[game->map.height - 1][i])
	{
		if (game->map.map[game->map.height - 1][i] != '1'
			&& game->map.map[game->map.height - 1][i] != ' ')
			return (-1);
		i++;
	}
	return (0);
}

int	check_border_walls(t_game *game)
{
	int	j;
	int	len;
	int	last_char_idx;

	if (check_first_last(game) != 0)
		return (-1);
	j = 0;
	while (j < game->map.height)
	{
		if (game->map.map[j][0] != '1' && game->map.map[j][0] != ' ')
			return (-1);
		len = ft_strlen(game->map.map[j]);
		if (len > 0)
		{
			last_char_idx = len - 1;
			while (last_char_idx >= 0 && game->map.map[j][last_char_idx] == ' ')
				last_char_idx--;
			if (last_char_idx >= 0 && game->map.map[j][last_char_idx] != '1')
				return (-1);
		}
		j++;
	}
	return (0);
}
