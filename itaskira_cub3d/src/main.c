#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: ./cub3D <map.cub>\n");
		return (1);
	}
	memset(&game, 0, sizeof(t_game));
	if (parse_file(&game, argv[1]) != 0)
	{
		cleanup_game(&game);
		return (1);
	}
	if (validate_map(&game) != 0)
	{
		cleanup_game(&game);
		return (1);
	}
	if (init_game(&game) != 0)
	{
		cleanup_game(&game);
		return (1);
	}
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
