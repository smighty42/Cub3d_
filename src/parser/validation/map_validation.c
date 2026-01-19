/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:34:24 by itaskira          #+#    #+#             */
/*   Updated: 2026/01/13 15:38:58 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdlib.h>
#include <unistd.h>

void	free_exit(t_game *game, const char *message)
{
	write(2, "Error: ", 7);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	gc_free_all(&game->gc);
	exit(EXIT_FAILURE);
}

int	validate_map(t_game *game)
{
	if (check_map_chars(game) != 0)
		free_exit(game, "Invalid characters in map");
	if (check_border_walls(game) != 0)
		free_exit(game, "Map borders not enclosed");
	if (check_enclosed_map(game) != 0)
		free_exit(game, "Map not properly enclosed");
	if (find_and_init_player(game) != 0)
		free_exit(game, "Player position not found");
	return (0);
}
