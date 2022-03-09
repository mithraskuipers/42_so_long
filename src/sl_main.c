/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 11:38:46 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/09 21:23:14 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!(game))
		exit_failure("Could not allocate memory for the game struct.");
	game->map.path = argv[1];
	check_input_validity(argc, argv);
	parse_map(game);
	game->mlx.instance = mlx_init();
	game->mlx.win = mlx_new_window(game->mlx.instance, game->px_col, \
	game->px_row, "Tamagotcha");
	if (!(game->mlx.win))
		exit_failure("Could not create window");
	store_xpm_paths(game);
	load_xpm(game);
	draw_map(game);
	mlx_key_hook(game->mlx.win, parse_input, (void *)&game->mlx);
	mlx_hook(game->mlx.win, 17, 0L, stop_game, game);
	mlx_loop(game->mlx.instance);

	system("leaks so_long");
	return (0);
}
