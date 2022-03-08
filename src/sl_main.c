/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 11:38:46 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/08 15:09:21 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!(game))
		exit_failure("Memory allocation issue.");
	game->map.path = argv[1];
	check_input_validity(argc, argv);
	parse_map(argc, argv, game);
	cell_looper(game, cell_count_map_chars);
	map_count_check(game);
	cell_looper(game, map_presence_borders);
	game->mlx.instance = mlx_init();
	game->mlx.win = mlx_new_window(game->mlx.instance, game->px_col, \
	game->px_row, "Tamagotcha");
	if (!(game->mlx.win))
		exit_failure("Could not create window");
	xpm_init(game);
	load_xpm_sprites(game);
	draw_map(game);
	mlx_key_hook(game->mlx.win, input, (void *)&game->mlx);
	mlx_hook(game->mlx.win, 17, 0L, stop_game, game);
	mlx_loop(game->mlx.instance);
	return (0);
}
