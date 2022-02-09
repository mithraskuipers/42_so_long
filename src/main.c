/* TODO: DIRECTION TRACKER */

#include "so_long.h"

int	main(int argc, char **argv)
{ 
	t_game	*game;

	//game = malloc(sizeof(t_game));
	game = ft_calloc(1, sizeof(t_game));
	if (!(game))
		ft_exit_failure("Memory allocation issue.");
	game->map.path = argv[1];
	
	//map_contents_init(game);
	check_input_validity(argc, argv);
	parse_map(game);
	cell_looper(game, cell_count_map_chars);
	cell_looper(game, map_presence_borders);
	map_count_check(game);
	game->mlx.instance = mlx_init();
	game->mlx.win = mlx_new_window(game->mlx.instance, game->px_col, game->px_row, "MITHRAS");
	if (!(game->mlx.win))
		ft_exit_failure("Could not create window");

	xpm_init(game);
	load_xpm_sprites(game);
	draw_map(game);
	//mlx_hook(game->mlx.win, 33, 1L << 17, exit_game, (void *)&game->mlx);
	mlx_hook(game->mlx.win, 2, (1L<<0), input, (void *)&game->mlx); // 2 = key down, (1L<<0) KeyPressMask
	mlx_loop(game->mlx.instance);
	return (0);
}

/*
int	exit_game(t_game *game)
{
	TODO!!!!
}
*/

int	input(int key, t_game *game)
{
	if (key == KEY_W)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_U].mlx_img;
		mover(game, game->map.player.up, 0, -1);
	}
	else if (key == KEY_S)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_D].mlx_img;
		mover(game, game->map.player.down, 0, 1);
	}
	else if (key == KEY_A)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_L].mlx_img;
		mover(game, game->map.player.left, -1, 0);
	}
	else if (key == KEY_D)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_R].mlx_img;
		mover(game, game->map.player.right, 1, 0);
	}
	mlx_clear_window(game->mlx.instance, game->mlx.win);
	draw_map(game);
	return (0);
}

static void mover(t_game *game, int dirtile, int x, int y)
{
	if ((dirtile != '0') && (dirtile != 'C') && (dirtile != 'E'))
		return ;
	
	if ((game->map.content.ncollected == game->map.content.ncollectables) && dirtile == 'E')
	{
		printf("YOU HAVE WON!!!!!");
		exit(1);
	}
	
	game->map.content.nsteps++;
	printf("You moved %d times.\n", game->map.content.nsteps);
	update_tiles(game, game->map.player.x, game->map.player.y, '0');
	update_tiles(game, (game->map.player.x + x), (game->map.player.y + y), 'P');
	game->map.player.y = game->map.player.y + y;
	game->map.player.x = game->map.player.x + x;
	update_awareness(game);
	//print_map(game);
}

static void update_tiles(t_game *game, int x, int y, char c)
{
	if (game->map.map[y][x] == 'C')
		game->map.content.ncollected++;
	game->map.map[y][x] = c;
}

static void update_awareness(t_game *game)
{
	game->map.player.up = game->map.map[game->map.player.y-1][game->map.player.x];
	game->map.player.down = game->map.map[game->map.player.y+1][game->map.player.x];
	game->map.player.left = game->map.map[game->map.player.y][game->map.player.x - 1];
	game->map.player.right = game->map.map[game->map.player.y][game->map.player.x + 1];
}

static void draw_player(t_game *game)
{
	mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[PLAYER].mlx_img, (game->map.player.x * TILE_WIDTH), (game->map.player.y * TILE_WIDTH));
}

/* DEBUGGING FUNCTIONS */

static void print_player_data(t_game *game)
{
	printf("Player position:\n");
	printf("row: %d\n", game->map.player.y);
	printf("col: %d\n", game->map.player.x);
	printf("Player state:\n");
	printf("up: %d\n", game->map.player.up);
	printf("down: %d\n", game->map.player.down);
	printf("left: %d\n", game->map.player.left);
	printf("right: %d\n", game->map.player.right);
}

static void draw_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map.ntiles_rows)
	{
		col = 0;
		while (col < game->map.ntiles_cols)
		{
			cell_player_data(game, row, col);
			cell_draw_bg(game, row, col);
			cell_draw_obstacles(game, row, col);
			cell_draw_corners(game, row, col);
			cell_draw_collectable(game, row, col);
			cell_draw_door(game, row, col);
			cell_player_pos(game, row, col);
			col++;
		}
		row++;
	}
	draw_player(game);
}

static void cell_player_data(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
	{
		// position
		game->map.player.x = col;
		game->map.player.y = row;
		// surrounding
		game->map.player.up = game->map.map[game->map.player.y-1][game->map.player.x];
		game->map.player.down = game->map.map[game->map.player.y+1][game->map.player.x];
		game->map.player.left = game->map.map[game->map.player.y][game->map.player.x - 1];
		game->map.player.right = game->map.map[game->map.player.y][game->map.player.x + 1];
	}
}

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
	while ((i < game->map.ntiles_rows) && (game->map.map[i])) // SEG FAULT
	{
		free (game->map.map[i]);
		i++;
	}
	free (game->map.map);
	ft_exit_failure(s);
}

static void	check_input_validity(int argc, char **argv)
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
	game->map.ntiles_cols = len;
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
	game->map.ntiles_rows = i;
	close(fd);
}

/*
static void	check_map_rectangular(t_game *game)
{
	if (game->map.ntiles_cols != game->map.ntiles_rows)
		ft_map_failure(game, "Map is not rectangular.");
}
*/

static void cell_count_map_chars(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
		(game->map.content.players)++;
	else if (game->map.map[row][col] == 'C')
		(game->map.content.ncollectables)++;
	else if (game->map.map[row][col] == 'E')
		(game->map.content.exits)++;
	else if ((!(game->map.map[row][col] != '0')) && (!(game->map.map[row][col] != '1')))
		(game->map.content.invalids)++;
}

static void map_count_check(t_game *game)
{
	if (game->map.content.players > 1)
		ft_map_failure(game, "Your map has more than 1 player spawnpoint.");
	if (game->map.content.players < 1)
		ft_map_failure(game, "Your map does not have 1 player spawnpoint.");
}

static void	map_presence_borders(t_game *game, int i, int j)
{
	if ((i == 0) || (i == (game->map.ntiles_rows) - 1))
	{
		if (game->map.map[i][j] != '1')
			ft_map_failure(game, "Your map is not enclosed in borders");
	}
	else
	{
		if ((game->map.map[i][0] != '1') || \
		(game->map.map[i][game->map.ntiles_cols - 1] != '1'))
				ft_map_failure(game, "Your map is not enclosed in borders");
	}
}

static void	read_map_into_memory(t_game *game, char *s, int row)
{
	game->map.fd = open(game->map.path, O_RDONLY);
	if (game->map.fd < 0)
	{
		close(game->map.fd);
		ft_exit_failure("Failing to read the map.");
	}
	row = 0;
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.ntiles_rows + 1));
	if (!(game->map.map))
		ft_exit_failure("Malloc error.");
	while (row < game->map.ntiles_rows)
	{
		s = get_next_line(game->map.fd);
		if (!s)
		{
			if (row > 0)
				ft_exit_failure("malloc error");
			if (row == 0)
				ft_exit_failure("kaart is leeg");
		}
		game->map.map[row] = s; // eigenlijk zet die m op x
		row++;
	}
	close(game->map.fd);
}

static void	parse_map(t_game *game)
{
	game->map.fd = open(game->map.path, O_RDONLY);
	get_map_width(game);
	get_map_height(game);
	//check_map_rectangular(game);
	game->px_row = game->map.ntiles_rows * TILE_WIDTH;
	game->px_col = game->map.ntiles_cols * TILE_WIDTH;
	read_map_into_memory(game, NULL, 0);
}

/* init functions */

static void xpm_init(t_game *game)
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
	game->img[CORNER_UL].path = "./assets/corner_ul.xpm";
	game->img[CORNER_UR].path = "./assets/corner_ur.xpm";
	game->img[CORNER_LL].path = "./assets/corner_ll.xpm";
	game->img[CORNER_LR].path = "./assets/corner_lr.xpm";
	game->img[COLLECTABLE].path = "./assets/collectable.xpm";
	game->img[DOOR_C].path = "./assets/door_c.xpm";
	game->img[DOOR_O].path = "./assets/door_o.xpm";
}

static void looper2(t_game *game, int pic, int *height, int *width)
{
	game->img[pic].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, game->img[pic].path, height, width);
}

static void	load_xpm_sprites(t_game *game)
{
	int row; // hoe werkt dit?
	int col; // hoe werkt dit??

	for (int i = 0; i < N_IMAGES; i++)
	{
		looper2(game, i, &game->img[i].height, &game->img[i].width);
	}

	// game->img[BG].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	// game->img[BG].path, p[BG].height, p[BG].width;
	// game->img[WALL_L].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	// game->img[WALL_L].path, p[WALL_L].height, p[WALL_L].width;
	// game->img[WALL_R].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	// game->img[WALL_R].path, p[WALL_R].height, p[WALL_R].width;
	// game->img[WALL_U].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	// game->img[WALL_U].path, p[WALL_U].height, p[WALL_U].width;
	// game->img[WALL_D].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	// game->img[WALL_D].path, p[WALL_D].height, p[WALL_D].width;
	// game->img[CORNER_UL].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	// game->img[CORNER_UL].path, p[CORNER_UL].height, p[CORNER_UL].width;
	// game->img[CORNER_UR].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	// game->img[CORNER_UR].path, p[CORNER_UR].height, p[CORNER_UR].width;
	// game->img[CORNER_LL].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	// game->img[CORNER_LL].path, p[CORNER_LL].height, p[CORNER_LL].width;
	// game->img[CORNER_LR].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance, \
	// game->img[CORNER_LR].path, p[CORNER_LR].height, p[CORNER_LR].width;
	// game->img[COLLECTABLE].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance,\
	// game->img[COLLECTABLE].path, p[COLLECTABLE].height, p[COLLECTABLE].width;
	// game->img[DOOR_C].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance,\
	// game->img[DOOR_C].path, p[DOOR_C].height, p[DOOR_C].width;
	// game->img[DOOR_O].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance,\
	// game->img[DOOR_O].path, p[DOOR_O].height, p[DOOR_O].width;
	// game->img[STONE].mlx_img =  mlx_xpm_file_to_image(game->mlx.instance,\
	// game->img[STONE].path, p[STONE].height, p[STONE].width;
}

/* loop functions */

static void cell_looper(t_game *game, void (*f)())
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

/* cell functions */

static void cell_draw_obstacles(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == '1')
	{
		row = (row * TILE_WIDTH);
		col = (col * TILE_WIDTH);
		if (col == 0)
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[WALL_L].mlx_img, col, row);
		else if (col == (TILE_WIDTH * (game->map.ntiles_cols - 1)))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[WALL_R].mlx_img, col, row);
		else if (row == 0)
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[WALL_U].mlx_img, col, row);
		else if (row == (TILE_WIDTH * (game->map.ntiles_rows - 1)))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[WALL_D].mlx_img, col, row);
		else
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[STONE].mlx_img, col, row);
	}
}

static void cell_draw_collectable(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'C')
	{
		row = (row * TILE_WIDTH);
		col = (col * TILE_WIDTH);
		mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[COLLECTABLE].mlx_img, col, row);
	}
}

static void cell_player_pos(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
	{
		game->map.player.y = row;
		game->map.player.x = col;
	}
}

static void cell_draw_player(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
	{
		mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[PLAYER].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
	}
}

static void cell_draw_door(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'E')
	{
		if (game->map.content.ncollectables != game->map.content.ncollected)
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[DOOR_C].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[DOOR_O].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
	}
}

static void cell_draw_bg(t_game *game, int row, int col)
{
	mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[BG].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
}

static void cell_draw_corners(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == '1')
	{
		if ((col == 0) && (row == 0))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[CORNER_UL].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if ((col == 0) && (row == (game->map.ntiles_rows - 1)))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[CORNER_LL].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if ((col == (game->map.ntiles_cols - 1)) && (row == 0))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[CORNER_UR].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if ((col == (game->map.ntiles_cols - 1)) && (row == (game->map.ntiles_rows - 1)))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[CORNER_LR].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
	}
}

static void cell_draw_playerinfo(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
	{
		game->map.player.x = col;
		game->map.player.y = row;
	}
}

/* print functions */

static void print_map(t_game *game)
{
	int row;

	row = 0;
	ft_putstr_fd("\r", 1);
	while (row < game->map.ntiles_rows)
	{
		ft_putstr_fd(game->map.map[row], 1);
		row++;
	}
	ft_putstr_fd("\n", 1);
}