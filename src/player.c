#include "../mlx/mlx.h"
#include "../cub3d.h"
#include <stdio.h>

void	put_player_if(t_game *game, char c)
{
	if (c == 'N')
		game->player.angle_eye = 3.0 * PI / 2;
	else if (c == 'S')
		game->player.angle_eye = PI / 2;
	else if (c == 'E')
		game->player.angle_eye = 0.0;
	else if (c == 'W')
		game->player.angle_eye = PI;
}

void	put_player(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			c = game->map.map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.x = j + 0.5;
				put_player_if(game, c);
			}
			j++;
		}
		i++;
	}
}
