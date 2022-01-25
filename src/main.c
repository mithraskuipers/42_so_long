#include "so_long.h"

int		ft_exit_failure(char *s)
{
	ft_putstr_fd("Error\n", 2); // Don't touch this. Subject wants this.
	ft_putstr_fd(s, 2);
	exit (EXIT_FAIL);
}



/*
int	open_file(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		ft_exit_failure("Failed to open the map.");
	return (fd);
}




void	read_texture_paths(t_game *game)
{
	game->img[0].path = "./assets/env0.xpm";
	game->img[1].path = "./assets/env1.xpm";
	game->img[2].path = "./assets/env2.xpm";
}

void	get_map_dim(t_game *game, char *filepath)
{
	int	fd;

	fd = open_file(filepath);
	game->map.filepath = filepath;
	game->map.width = map_width(fd);
	game->map.height = map_height(fd, game->map.width);
	game->win_px_x = game->map.width * TILE_WIDTH;
	game->win_px_y = game->map.height * TILE_WIDTH;
}


static void	check_input_validity(t_game *game)
{

}
*/






int		check_input_validity(int argc, char **argv)
{
	int	fd;
	if (argc < 2)
		ft_exit_failure("Please provide a map.");
	if (!(ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))) // werkt dit?
		ft_exit_failure("Please provide a map with .ber extension.");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		ft_exit_failure("Please provide a valid map.");
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
	game->map.n_xtiles = len;
}

static void	get_map_height(t_game *game)
{
	int fd;
	int i;

	fd = open(game->map.filepath, O_RDONLY);
	// IF FD FAILS.....vergeet ook geen close
	i = 0;
	while (get_next_line(game->map.fd))
		i++;

	game->map.n_ytiles = i;



	/*
	char	buff[1];
	int		count;
	int		nbytes;
	int		i;

	count = 1;
	nbytes = 1;
	i = 0;
	buff[0] = '\0';

	while (nbytes)
	{
		nbytes = read(game->map.fd, buff, 1);
		if (i == ((game->map.n_xtiles * TILE_WIDTH) / TILE_WIDTH))
		{
			count++;
			i = 0;
		}
		else
			i++;
	}
	game->map.n_ytiles = count;
	*/
}

static void	check_map_rectangular(t_game *game)
{
	if (!(game->map.n_xtiles == game->map.n_ytiles))
		ft_exit_failure("Map is not rectangular.");
}

/*
static void	check_map_contents(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.n_ytiles)
	{
		j = 0;
		while (j < game->map.n_xtiles)
		{
			j++;
			// TODO. Will now use Row Column indexing to check contents
		}
		i++;
	}
}
*/

static void	read_map_into_memory(t_game *game)
{
	game->map.fd = open(game->map.filepath, O_RDONLY);
	if (game->map.fd < 0)
	{
		close(game->map.fd);
		ft_exit_failure("Please provide a valid map.");
	}
	int i;

	i = 0;
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.n_ytiles + 1));
	if (!(game->map.map))
		ft_exit_failure("Malloc error.");
	while (i < game->map.n_ytiles)
	{
		//printf("%s", get_next_line(game->map.fd));
		game->map.map[i] = get_next_line(game->map.fd);
		i++;
	}
	close(game->map.fd);
}

static void	parse_map(t_game *game)
{
	game->map.fd = open(game->map.filepath, O_RDONLY);
	get_map_width(game);
	get_map_height(game);
	check_map_rectangular(game);
	read_map_into_memory(game);
	//check_map_contents(game);
}

static void	validity(int argc, char **argv, t_game *game)
{
	check_input_validity(argc, argv);
	parse_map(game);
}


static void init(char **argv, t_game *game)
{
	game->map.filepath = argv[1];
	game->map.n_xtiles = 0;
	game->map.n_ytiles = 0;
}

// ALS FD == -1, voeg dan ook ft error toe!

// GEBRUIK GET NEXT LINE VOOR INLEZEN VAN DE KAART!


int			main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!(game))
		ft_exit_failure("Memory allocation issue.");
	init(argv, game);
	validity(argc, argv, game);
	printf("%s", game->map.map[0]);


	//printf("%d", game->map.n_xtiles);
	//printf("%d", game->map.n_ytiles);




	//printf("%s", game->map.filepath);
	//printf("\n");
	//printf("%d", game->map.fd);



	/*
	get_map_dim(game, argv[1]);
	game->mlx.init = mlx_init();
	if (!(game->mlx.init))
		ft_exit_failure("MLX initialization failed.");
	read_texture_paths(game);
	create_images(game);
	game->mlx.win = mlx_new_window(game->mlx.init, game->win_px_x, game->win_px_y, "so_long window");
	if (!(game->mlx.win))
		return (ft_exit_failure("MLX window creation fail."));
	draw_bg(game);
	mlx_loop(game->mlx.init);
	*/
	return (0);
}