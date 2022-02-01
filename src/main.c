#include "so_long.h"


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
	cell_looper_ptr(game, map_count);
	cell_looper_ptr(game, map_count_check);
	cell_looper_ptr(game, map_presence_borders);
	cell_looper_ptr(game, count_chars_sub);
	game->mlx.instance = mlx_init();
	game->mlx.win = mlx_new_window(game->mlx.instance, game->px_row, game->px_col, "MITHRAS");
	if (!(game->mlx.win))
		ft_exit_failure("Could not create window");
	xpm_init(game);
	xpm_loader(game);
	draw_map(game);



	//cell_looper(game);
	//cell_looper_ptr(game, paint_player);
	//mlx_hook(game->mlx.win, 2, (1L<<0), input, (void *)&game); // 2 = key down, (1L<<0) KeyPressMask
	//mlx_loop(game->mlx.instance);
	//get_player_state_standalone(game);
	//printf("\nrow %d\n", game->map.player_state.pos_row);
	//printf("\ncol %d\n", game->map.player_state.pos_col);
	//printf("%d", game->map.player_state.tile_up);
	//printf("%d", game->map.player_state.tile_down);
	//get_player_pos_ptr(game);
	//print_player_state(game);
	//print_player_pos(game);
	//paint_player(game);
	//mlx_loop_hook(game->mlx.instance, update, game); // for each new frame it runs update()
	//mlx_loop(game->mlx.instance);
	return (0);
}

static void draw_map(t_game *game)
{
	cell_looper_ptr(game, paint_bg);
	cell_looper_ptr(game, paint_walls);
	cell_looper_ptr(game, paint_corners);
	cell_looper_ptr(game, paint_player);
	mlx_loop(game->mlx.instance);
}

static void paint_player(t_game *game, int x, int y)
{
	if (game->map.map[y][x] == 'P')
	{
		mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[PLAYER].mlx_img, (x * TILE_WIDTH), (y * TILE_WIDTH));
	}
}

/* All valid input keys */
enum e_keycode
{
	KEY_UP = 13,
	KEY_DOWN = 1,
	KEY_LEFT = 0,
	KEY_RIGHT = 2,
	RESET = 15,
	ESC = 53
};

static void print_player_pos(t_game *game)
{
	printf("Player position:\n");
	printf("row: %d\n", game->map.player_state.pos_row);
	printf("col: %d\n", game->map.player_state.pos_col);
}

static void print_player_state(t_game *game)
{
	printf("Player state:\n");
	printf("up: %d\n", game->map.player_state.tile_up);
	printf("down: %d\n", game->map.player_state.tile_down);
	printf("left: %d\n", game->map.player_state.tile_left);
	printf("right: %d\n", game->map.player_state.tile_right);
}

static void get_player_pos_ptr(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
	{
		game->map.player_state.pos_col = col;
		game->map.player_state.pos_row = row;
	}
}

static void get_player_state_standalone(t_game *game)
{
	game->map.player_state.tile_up = game->map.map[game->map.player_state.pos_row-1][game->map.player_state.pos_col];
	game->map.player_state.tile_down = game->map.map[game->map.player_state.pos_row+1][game->map.player_state.pos_col];
	game->map.player_state.tile_left = game->map.map[game->map.player_state.pos_row][game->map.player_state.pos_col - 1];
	game->map.player_state.tile_right = game->map.map[game->map.player_state.pos_row][game->map.player_state.pos_col + 1];
}

static void move_up(t_game *game)
{
	if (game->map.player_state.tile_up == '0')
	{
		game->map.player_state.pos_row = game->map.player_state.pos_row - 1;
		game->map.player_state.pos_col = game->map.player_state.pos_col;
		get_player_state_standalone(game);
	}
	else
	{
		printf("MOVEMENT NOT ALLOWED\n");
	}
}

int	input(int key, t_game *game)
{
	if (key == KEY_UP)
	{
		move_up(game);
	}
}

// MAAK 1 SUPER BEELD PRINTER FUNCTIE.
// DIE ROEP JE 1x aan EN HIJ PARSED HEEL DE KAART EN TEKENT DE SPRITES

// Functie leest ook werkelijk de inhoud van de kaart uit!
// Dus kan worden gebruikt om de betekenis te parsen. 
// Leest dus niet enkel de coordinaten uit van up/down/left/right, heb je ook niets aan!

static void cell_looper(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map.ntiles_rows)
	{
		col = 0;
		while (col < game->map.ntiles_cols)
		{
			paint_bg(game, row, col);
			get_player_pos_ptr(game, row, col);
			//paint_player(game, row, col);
			//paint_walls(game, row, col); // tekent de muren ook op de hoeken
			//paint_corners(game, row, col); // superimposed de hoeken
			col++;
		}
		row++;
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
	while ((i < game->map.ntiles_rows) && (game->map.map[i]))
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

static void	check_map_rectangular(t_game *game)
{
	if (game->map.ntiles_cols != game->map.ntiles_rows)
		ft_map_failure(game, "Map is not rectangular.");
}


static void count_chars_sub(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
		(game->map.content.players)++;
	else if (game->map.map[row][col] == 'C')
		(game->map.content.collectables)++;
	else if (game->map.map[row][col] == 'E')
		(game->map.content.exits)++;
	else if ((!(game->map.map[row][col] != '0')) && (!(game->map.map[row][col] != '1')))
		(game->map.content.invalids)++;
}

/*
static void	check_map_contents1(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.ntiles_rows)
	{
		j = 0;
		while (j < game->map.ntiles_cols)
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
*/

static void	map_count(t_game *game, int i, int j)
{

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

static void map_count_check(t_game *game)
{
	if (game->map.content.players > 1)
		ft_map_failure(game, "You map has more than 1 player spawnpoint.");
	if (game->map.content.players < 1)
		ft_map_failure(game, "You map does not have 1 player spawnpoint.");
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
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.ntiles_rows + 1));
	if (!(game->map.map))
		ft_exit_failure("Malloc error.");
	while (row < game->map.ntiles_rows)
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
	game->px_row = game->map.ntiles_rows * TILE_WIDTH;
	game->px_col = game->map.ntiles_cols * TILE_WIDTH;
	read_map_into_memory(game);
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
	game->img[PLAYER].path = "./assets/player_right.xpm";
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

static void paint_bg(t_game *game, int row, int col)
{
	mlx_put_image_to_window(game->mlx.instance, game->mlx.win, game->img[BG].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
}

static void paint_corners(t_game *game, int row, int col)
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



static void paint_walls(t_game *game, int row, int col)
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
}

static void print_map(t_game *game)
{
	int row;

	row = 0;
	printf("\r");
	while (row < game->map.ntiles_rows)
	{
		ft_putstr_fd(game->map.map[row], 1);
		row++;
	}
	ft_putstr_fd("\n", 1);
}

static void cell_looper_ptr(t_game *game, void (*f)())
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