/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 19:13:10 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/02/11 19:20:020 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// TODO: CHECK FOR E (EXIT)
// Todo teken stenen als 1 aan binnenkant

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
	game->px_row, "MITHRAS");
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
	if (key == KEY_UP || key == KEY_UPARROW)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_U].mlx_img;
		mover(game, game->map.player.u, 0, -1);
	}
	else if (key == KEY_DOWN || key == KEY_DOWNARROW)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_D].mlx_img;
		mover(game, game->map.player.d, 0, 1);
	}
	else if (key == KEY_LEFT || key == KEY_LEFTARROW)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_L].mlx_img;
		mover(game, game->map.player.l, -1, 0);
	}
	else if (key == KEY_RIGHT || key == KEY_RIGHTARROW)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_R].mlx_img;
		mover(game, game->map.player.r, 1, 0);
	}
	else if (key == ESC)
		close_win(game);
	// mlx_clear_window(game->mlx.instance, game->mlx.win);
	draw_map(game);
	return (0);
}

void mover(t_game *game, int dirtile, int x, int y)
{
	if ((dirtile != '0') && (dirtile != 'C') && (dirtile != 'E'))
		return ;
	if (dirtile == 'E')
	{
		if (game->map.content.ncollected == game->map.content.ncollectables)
			exit(1);
		else
			return ;
	}
	game->map.content.nsteps++;
	ft_printf("You moved %d times.\n", game->map.content.nsteps);
	update_tiles(game, game->map.player.x, game->map.player.y, '0');
	update_tiles(game, (game->map.player.x + x), (game->map.player.y + y), 'P');
	game->map.player.y = game->map.player.y + y;
	game->map.player.x = game->map.player.x + x;
	update_awareness(game, &game->map.player);
}

void update_tiles(t_game *game, int x, int y, char c)
{
	if (game->map.map[y][x] == 'C')
		game->map.content.ncollected++;
	game->map.map[y][x] = c;
}

void update_awareness(t_game *game, t_state *player)
{
	player->u = game->map.map[player->y-1][player->x];
	player->d = game->map.map[player->y+1][player->x];
	player->l = game->map.map[player->y][player->x-1];
	player->r = game->map.map[player->y][player->x+1];
}

void draw_player(t_game *game)
{
	mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
	game->img[PLAYER].mlx_img, (game->map.player.x * TILE_WIDTH), \
	(game->map.player.y * TILE_WIDTH));
}

void draw_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map.ntiles_rows)
	{
		col = 0;
		while (col < game->map.ntiles_cols)
		{
			cell_player(game, row, col, &game->map.player);
			cell_draw_bg(game, row, col);
			cell_draw_collectable(game, row, col);
			cell_draw_door(game, row, col);
			cell_draw_walls(game, row, col);
			cell_draw_corners(game, row, col);
			cell_player_pos(game, row, col);
			col++;
		}
		row++;
	}
	draw_player(game);
}

void cell_player(t_game *game, int row, int col, t_state *player)
{
	if (game->map.map[row][col] == 'P')
	{
		player->x = col;
		player->y = row;
		player->u = game->map.map[player->y-1][player->x];
		player->d = game->map.map[player->y+1][player->x];
		player->l = game->map.map[player->y][player->x-1];
		player->r = game->map.map[player->y][player->x+1];
	}
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

void get_dim(t_game *game, int fd, char *tmp, int ret)
{
	ret = get_next_line(fd, &tmp);
	if (ret > 0)
		game->map.ntiles_cols = ft_strlen(tmp);
	else if (ret == 0)
		ft_exit_failure("Map is empty.");
	while (ret)
	{
		ret = get_next_line(fd, &tmp);
		if (ret == -1)
			break;
		if ((ft_strlen(tmp)) != (size_t)game->map.ntiles_cols)
		{
			free(tmp);
			ft_exit_failure("Map is not Rectangle.");
		}
		game->map.ntiles_rows++;
	}
	game->map.ntiles_rows++;
	close(fd);
	if (ret < 0)
		ft_exit_failure("File could not be read.");
}

void cell_count_map_chars(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
		(game->map.content.players)++;
	else if (game->map.map[row][col] == 'C')
		(game->map.content.ncollectables)++;
	else if (game->map.map[row][col] == 'E')
		(game->map.content.exits)++;
	else if ((!(game->map.map[row][col] != '0')) && \
	(!(game->map.map[row][col] != '1')))
		(game->map.content.invalids)++;
}

void map_count_check(t_game *game)
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

void	read_map_into_memory(t_game *game, int row)
{
	game->map.fd = open(game->map.path, O_RDONLY);
	if (game->map.fd < 0)
	{
		close(game->map.fd);
		ft_exit_failure("Failing to read the map.");
	}
	row = 0;
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.ntiles_rows+1));
	if (!(game->map.map))
		ft_exit_failure("Malloc error.");
	while (row < game->map.ntiles_rows)
	{
		int ret = get_next_line(game->map.fd, &game->map.map[row]);
		if (ret < 0)
			ft_exit_failure("Failing to read the map.");
		row++;
	}
	close(game->map.fd);
}

void	parse_map(int argc, char **argv, t_game *game)
{
	if (argc < 2)
		ft_exit_failure("Please provide a map.");
	if (ft_strrchr(argv[1], '.') == 0 || ft_strncmp(ft_strrchr(argv[1], '.'), ".ber", 5))
		ft_exit_failure("Please provide a map with .ber extension.");
	game->map.fd = open(game->map.path, O_RDONLY);
	if (game->map.fd < 0)
	{
		close(game->map.fd);
		ft_exit_failure("Error while reading the map. fd < 0");
	}
	get_dim(game, game->map.fd, 0, 0);
	game->px_row = game->map.ntiles_rows * TILE_WIDTH;
	game->px_col = game->map.ntiles_cols * TILE_WIDTH;
	read_map_into_memory(game, 0);
}

/* init functions */

void xpm_init(t_game *game)
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

void looper(t_game *game, int pic, int *height, int *width)
{
	game->img[pic].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	game->img[pic].path, height, width);
}

void	load_xpm_sprites(t_game *game)
{
	for (int i = 0; i < N_IMAGES; i++)
	{
		looper(game, i, &game->img[i].height, &game->img[i].width);
	}
}

void cell_looper(t_game *game, void (*f)())
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map.ntiles_rows)
	{
		col = 0;
		while (col < game->map.ntiles_cols)
		{
			f(game, row, col);
			col++;
		}
		row++;
	}
}

void cell_draw_walls(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == '1')
	{
		if (row == 0)
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_U].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if (row == (game->map.ntiles_rows-1))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_D].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if (col == 0)
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_L].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if (col == (game->map.ntiles_cols-1))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_R].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[STONE].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
	}
}

void cell_draw_collectable(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'C')
	{
		row = (row * TILE_WIDTH);
		col = (col * TILE_WIDTH);
		mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
		game->img[COLLECTABLE].mlx_img, col, row);
	}
}

void cell_player_pos(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
	{
		game->map.player.y = row;
		game->map.player.x = col;
	}
}

void cell_draw_door(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'E')
	{
		if (game->map.content.ncollectables != game->map.content.ncollected)
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[DOOR_C].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[DOOR_O].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
	}
}

void cell_draw_bg(t_game *game, int row, int col)
{
	mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[BG].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
}

void cell_draw_corners(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == '1')
	{
		if ((col == 0) && (row == 0))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_UL].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if ((col == 0) && (row == (game->map.ntiles_rows-1)))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_LL].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if ((col == (game->map.ntiles_cols-1)) && (row == 0))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_UR].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if ((col == (game->map.ntiles_cols-1)) && \
		(row == (game->map.ntiles_rows-1)))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_LR].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
	}
}
