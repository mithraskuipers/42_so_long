/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 11:38:46 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/08 11:48:57 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!(game))
		ft_exit_failure("Memory allocation issue.");
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
		ft_exit_failure("Could not create window");
	xpm_init(game);
	load_xpm_sprites(game);
	draw_map(game);
	mlx_key_hook(game->mlx.win, input, (void *)&game->mlx);
	mlx_hook(game->mlx.win, 17, 0L, close_win, game);
	mlx_loop(game->mlx.instance);
	return (0);
}

int	input(int key, t_game *game)
{
	if (key == KEY_UP)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_U].mlx_img;
		mover(game, game->map.player.u, 0, -1);
	}
	else if (key == KEY_DOWN)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_D].mlx_img;
		mover(game, game->map.player.d, 0, 1);
	}
	else if (key == KEY_LEFT)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_L].mlx_img;
		mover(game, game->map.player.l, -1, 0);
	}
	else if (key == KEY_RIGHT)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_R].mlx_img;
		mover(game, game->map.player.r, 1, 0);
	}
	else if (key == ESC)
		close_win(game);
	mlx_clear_window(game->mlx.instance, game->mlx.win);
	draw_map(game);
	return (0);
}

void	ft_map_failure(t_game *game, char *s)
{
	int	i;

	i = 0;
	while ((i < game->map.ntiles_rows) && (game->map.map[i]))
	{
		free (game->map.map[i]);
		i++;
	}
	free (game->map.map);
	ft_exit_failure(s);
}

void	check_input_validity(int argc, char **argv)
{
	int	fd;

	if (argc < 2)
		ft_exit_failure("Please provide a map.");
	if (!(ft_strnstr(argv[1], ".ber", ft_strlen(argv[1]))))
		ft_exit_failure("Please provide a map with .ber extension.");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		ft_exit_failure("Error while reading the map. fd < 0");
	}
	close(fd);
}

void	map_count_check(t_game *game)
{
	if (game->map.content.players > 1)
		ft_exit_failure("Your map has more than 1 player spawnpoint.");
	else if (game->map.content.players < 1)
		ft_exit_failure("Your map does not have 1 player spawnpoint.");
	if (game->map.content.exits > 1)
		ft_exit_failure("Your map has more than 1 exit.");
	else if (game->map.content.exits < 1)
		ft_exit_failure("Your map does not have 1 exit.");
}

void	map_presence_borders(t_game *game, int i, int j)
{
	if ((i == 0) || (i == (game->map.ntiles_rows)-1))
	{
		if (game->map.map[i][j] != '1')
			ft_map_failure(game, "Your map is not enclosed in borders");
	}
	if ((j == 0) || (j == (game->map.ntiles_cols)-1))
	{
		if (game->map.map[i][j] != '1')
			ft_map_failure(game, "Your map is not enclosed in borders");
	}
}

void	xpm_init(t_game *game)
{
	game->img[BG].path = "./assets/BG.xpm";
	game->img[WALL_L].path = "./assets/wall_l.xpm";
	game->img[WALL_R].path = "./assets/wall_r.xpm";
	game->img[WALL_U].path = "./assets/wall_u.xpm";
	game->img[WALL_D].path = "./assets/wall_d.xpm";
	game->img[PLAYER].path = "./assets/player_front.xpm";
	game->img[PLAYER_L].path = "./assets/player_left.xpm";
	game->img[PLAYER_R].path = "./assets/player_right.xpm";
	game->img[PLAYER_U].path = "./assets/player_back.xpm";
	game->img[PLAYER_D].path = "./assets/player_front.xpm";
	game->img[WALL_UL].path = "./assets/WALL_ul.xpm";
	game->img[WALL_UR].path = "./assets/WALL_ur.xpm";
	game->img[WALL_LL].path = "./assets/WALL_ll.xpm";
	game->img[WALL_LR].path = "./assets/WALL_lr.xpm";
	game->img[COLLECTABLE].path = "./assets/collectable.xpm";
	game->img[DOOR_C].path = "./assets/door_c.xpm";
	game->img[DOOR_O].path = "./assets/door_o.xpm";
	game->img[STONE].path = "./assets/stone.xpm";
}

void	load_xpm_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < N_IMAGES)
	{
		game->img[i].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
		game->img[i].path, &game->img[i].height, &game->img[i].width);
		i++;
	}
}
