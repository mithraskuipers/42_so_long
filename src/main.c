#include "so_long.h"

/*
clear && make re && clear && ./so_long map1_5x5.ber
*/

static void	ft_exit_failure(char *s)
{
	ft_putstr_fd("Error\n", 2); // Don't touch this. Subject wants this.
	ft_putstr_fd(s, 2);
	exit (EXIT_FAIL);
}

static void	ft_map_failure(t_game *game, char *s)
{
	int	i;

	i = 0;
	while ((i < game->map.ntiles_y) && (game->map.map[i]))
	{
		free (game->map.map[i]);
		i++;
	}
	free (game->map.map);
	ft_exit_failure(s);
}

int		check_input_validity(int argc, char **argv)
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
	return (0);
}

static void	get_map_width(t_game *game)
{
	char	buff[1];
	int		len;
	int		nbytes;

	buff[0] = '\0';
	nbytes = 1;
	len = 0;
	while (nbytes)
	{
		nbytes = read(game->map.fd, buff, 1);
		if (buff[0] != '\n')
			len++;
		else
			break ;
	}
	game->map.ntiles_x = len;
}

static void	get_map_height(t_game *game)
{
	int fd;
	int i;

	fd = open(game->map.path, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		ft_exit_failure("File could not be opened.");
	}
	i = 1;
	while (get_next_line(game->map.fd))
		i++;
	game->map.ntiles_y = i;
	close(fd);
}

static void	check_map_rectangular(t_game *game)
{
	if (game->map.ntiles_x != game->map.ntiles_y)
		ft_map_failure(game, "Map is not rectangular.");
}

static void	check_map_contents1(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.ntiles_y)
	{
		j = 0;
		while (j < game->map.ntiles_x)
		{
			j++;
			if (game->map.map[i][j] == 'P')
				(game->map.content.players)++;
			else if (game->map.map[i][j] == 'C')
				(game->map.content.collectables)++;
			else if (game->map.map[i][j] == 'E')
				(game->map.content.exits)++;
			else if ((!(game->map.map[i][j] != '0')) && \
			(!(game->map.map[i][j] != '1')))
				(game->map.content.invalids)++;
		}
		i++;
	}
}

static void	check_map_contents2(t_game *game)
{
	if (game->map.content.players > 1)
		ft_map_failure(game, "You map has more than 1 player spawnpoint.");
	if (game->map.content.players < 1)
		ft_map_failure(game, "You map does not have 1 player spawnpoint.");
}

static void	check_map_borders(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.ntiles_y)
	{
		j = 0;
		if ((i == 0) || (i == (game->map.ntiles_y) - 1))
		{
			while (j < game->map.ntiles_x)
			{
				if (game->map.map[i][j] != '1')
					ft_map_failure(game, "Your map is not enclosed in borders");
				j++;
			}
		}
		else
		{
			if ((game->map.map[i][0] != '1') || \
			(game->map.map[i][game->map.ntiles_x - 1] != '1'))
					ft_map_failure(game, "Your map is not enclosed in borders");
			j++;
		}
		i++;
	}
}

static void	read_map_into_memory(t_game *game)
{
	int row;
	game->map.fd = open(game->map.path, O_RDONLY);
	if (game->map.fd < 0)
	{
		close(game->map.fd);
		ft_exit_failure("Failing to read the map.");
	}
	row = 0;
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.ntiles_y + 1));
	if (!(game->map.map))
		ft_exit_failure("Malloc error.");
	while (row < game->map.ntiles_y)
	{
		game->map.map[row] = get_next_line(game->map.fd); // eigenlijk zet die m op x
		row++;
	}
	close(game->map.fd);
}

static void	parse_map(t_game *game)
{
	game->map.fd = open(game->map.path, O_RDONLY);
	get_map_width(game);
	get_map_height(game);
	check_map_rectangular(game);
	game->px_x = game->map.ntiles_x * TILE_WIDTH;
	game->px_y = game->map.ntiles_y * TILE_WIDTH;
	read_map_into_memory(game);
	check_map_contents1(game);
	check_map_contents2(game);
	check_map_borders(game);
}

static void map_contents_init(t_game *game)
{
	game->map.content.players = 0;
	game->map.content.collectables = 0;
	game->map.content.exits = 0;
	game->map.content.invalids = 0;
}

static void xpm_init(t_game *game)
{
	game->img[BG].path = "./assets/bg.xpm";
	game->img[WALL_L].path = "./assets/wall_l.xpm";
	game->img[WALL_R].path = "./assets/wall_r.xpm";
	game->img[WALL_D].path = "./assets/wall_d.xpm";
	game->img[WALL_U].path = "./assets/wall_u.xpm";
	game->img[PLAYER].path = "./assets/player.xpm";
	game->img[CORNER_UL].path = "./assets/corner_ul.xpm";
	game->img[CORNER_UR].path = "./assets/corner_ur.xpm";
	game->img[CORNER_LL].path = "./assets/corner_ll.xpm";
	game->img[CORNER_LR].path = "./assets/corner_lr.xpm";
}

static void	xpm_loader(t_game *game)
{
	int row; // hoe werrowt dit?
	int col; // hoe werrowt dit??

	game->img[BG].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	game->img[BG].path, &row, &col);
	game->img[WALL_L].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	game->img[WALL_L].path, &row, &col);
	game->img[WALL_R].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	game->img[WALL_R].path, &row, &col);
	game->img[WALL_U].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	game->img[WALL_U].path, &row, &col);
	game->img[WALL_D].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	game->img[WALL_D].path, &row, &col);
	game->img[PLAYER].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	game->img[PLAYER].path, &row, &col);
	game->img[CORNER_UL].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	game->img[CORNER_UL].path, &row, &col);
	game->img[CORNER_UR].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	game->img[CORNER_UR].path, &row, &col);
	game->img[CORNER_LL].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	game->img[CORNER_LL].path, &row, &col);
	game->img[CORNER_LR].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	game->img[CORNER_LR].path, &row, &col);
}

/*
static void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	//draw_bg(game);
	//draw_walls(game);
	while (y < (game->map.ntiles_y))
	{
		x = 0;
		while (x < (game->map.ntiles_x))
		{
			superimpose_tile(game, x, y);
			x = x + 1;
		}
		y = y + 1;
	}
}
*/

// Het gaat goed zodra ik 2 coordinaten heb.
// 1e is dan x
// 2e is dan y

static void cell_checker(t_game *game, void (*f)())
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (col < game->map.ntiles_y)
	{
		row = 0;
		while (row < game->map.ntiles_x)
		{
			f(game, row, col); // row<-->col verandert niets
			row++;
		}
		col++;
	}
}

static void bg_painter(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[BG].mlx_img, (x * TILE_WIDTH), (y * TILE_WIDTH));
}

static void corner_painter(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == '1')
	{
		if ((col == 0) && (row == 0))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[CORNER_UL].mlx_img, (row * TILE_WIDTH), (col * TILE_WIDTH));
		else if ((col == 0) && (row == (game->map.ntiles_y - 1)))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[CORNER_UR].mlx_img, (row * TILE_WIDTH), (col * TILE_WIDTH));
		else if ((col == (game->map.ntiles_x - 1)) && (row == 0))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[CORNER_LL].mlx_img, (row * TILE_WIDTH), (col * TILE_WIDTH));
		else if ((col == (game->map.ntiles_x - 1)) && (row == (game->map.ntiles_y - 1)))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[CORNER_LR].mlx_img, (row * TILE_WIDTH), (col * TILE_WIDTH));
	}
}

static void player_painter(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
		mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[PLAYER].mlx_img, (row * TILE_WIDTH), (col * TILE_WIDTH));
}

static void wall_painter(t_game *game, int row, int y)
{
	row = (row * TILE_WIDTH);
	y = (y * TILE_WIDTH);
	while (y < game->px_y)
	{
		row = 0;
		while (row < game->px_x)
		{
			if (row == 0)
				mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[WALL_L].mlx_img, row, y);
			else if (row == (TILE_WIDTH * (game->map.ntiles_x - 1)))
				mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[WALL_R].mlx_img, row, y);
			else if (y == 0)
				mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[WALL_U].mlx_img, row, y);
			else if (y == (TILE_WIDTH * (game->map.ntiles_y - 1)))
				mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[WALL_D].mlx_img, row, y);
			row = row + TILE_WIDTH;
		}
		y = y + TILE_WIDTH;
	}
}

static void find_player_pos(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
	{
		game->map.p_pos.row = row;
		game->map.p_pos.col = col;
	}
}

static void cell_checker_main(t_game *game)
{
	cell_checker(game, bg_painter);
	cell_checker(game, wall_painter);
	cell_checker(game, corner_painter);
	cell_checker(game, find_player_pos);
	cell_checker(game, player_painter);
}

static void map_printer(t_game *game)
{
	int row;

	row = 0;
	while (row < game->map.ntiles_y)
	{
		ft_putstr_fd(game->map.map[row], 1);
		row++;
	}
}


int	main(int argc, char **argv)
{ 
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!(game))
		ft_exit_failure("Memory allocation issue.");
	game->map.path = argv[1];
	map_contents_init(game);
	check_input_validity(argc, argv);
	parse_map(game);
	game->mlx.instance = mlx_init();
	game->mlx.win = mlx_new_window(game->mlx.instance, game->px_x, game->px_y, "MITHRAS");
	if (!(game->mlx.win))
		ft_exit_failure("Could not create window");
	xpm_init(game);
	xpm_loader(game);
	cell_checker(game, find_player_pos);
	cell_checker_main(game);
	mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[PLAYER].mlx_img, game->map.p_pos.col* TILE_WIDTH, game->map.p_pos.row * TILE_WIDTH);
	//map_printer(game);
	mlx_loop(game->mlx.instance);
	printf("%c", game->map.map[1][8]); // print P
	return (0);
}




// Update map
// Clean mapß
// Redraw dan de map!

/*
prototype mlx_hook
int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
*/
